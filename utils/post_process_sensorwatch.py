import re

NAME_LEN = 6
ALLOWED_CHARS = (
    " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~ "
)

ZONE_NAMES_RE = re.compile(
    r'const unsigned char zone_names\[\d+\]\s*=\s*\{(.*?)\};',
    re.S
)
ZONE_DEFNS_RE = re.compile(
    r'const uzone_packed_t zone_defns\[\d+\]\s*=\s*\{(.*?)\};',
    re.S
)
UTZ_DEFINE_RE = re.compile(r"#define\s+(UTZ_[A-Z0-9_]+)\s+(\d+)")

def sanitize_char(c):
    if c == '\\':
        return ' '
    return c if c in ALLOWED_CHARS else ' '

def rewrite_zones(c_path, h_path):
    # ---------- Load zones.c ----------
    with open(c_path, "r", encoding="utf-8") as f:
        text = f.read()

    # ---------- Parse zone_names ----------
    zn_match = ZONE_NAMES_RE.search(text)
    if not zn_match:
        raise RuntimeError("zone_names not found")

    tokens = re.findall(r"'(.)'|(\d+)", zn_match.group(1))
    zone_names = []
    i = 0
    while i < len(tokens):
        name_chars = []
        while i < len(tokens) and tokens[i][1] == '':
            name_chars.append(tokens[i][0])
            i += 1
        if tokens[i][1] != '0':
            raise RuntimeError("Expected NUL after zone name")
        i += 1
        idx = int(tokens[i][1])
        i += 1

        padded = (
            [sanitize_char(c) for c in name_chars][:NAME_LEN]
            + [' '] * (NAME_LEN - len(name_chars))
        )
        zone_names.append({
            "orig_idx": idx,
            "name": padded
        })

    # ---------- Parse zone_defns ----------
    zd_match = ZONE_DEFNS_RE.search(text)
    if not zd_match:
        raise RuntimeError("zone_defns not found")

    defns_raw = re.findall(r"\{([^}]+)\}", zd_match.group(1))
    zone_defns = []
    for idx, raw in enumerate(defns_raw):
        parts = [int(x.strip()) for x in raw.split(",")]
        zone_defns.append({
            "orig_idx": idx,
            "data": parts,               # [offset, rule, abbrev, zone_idx]
            "key": (parts[0], parts[1], parts[2])
        })

    # ---------- Attach behavior data to names ----------
    by_idx = {z["orig_idx"]: z for z in zone_defns}
    for z in zone_names:
        d = by_idx[z["orig_idx"]]["data"]
        z["offset"] = d[0]
        z["rule"] = d[1]
        z["abbrev"] = d[2]
        z["key"] = (d[0], d[1], d[2])

    # ---------- Sort by behavior ----------
    zone_names.sort(key=lambda z: z["key"])

    # ---------- Deduplicate by (offset, rule, abbrev) ----------
    seen = set()
    deduped = []
    for z in zone_names:
        if z["key"] in seen:
            continue
        seen.add(z["key"])
        deduped.append(z)

    # ---------- Rebuild zone_names + zone_defns ----------
    out_bytes = bytearray()
    new_zone_names_lines = []
    new_zone_defns_lines = []
    old_to_new = {}

    for new_idx, z in enumerate(deduped):
        old_idx = z["orig_idx"]
        old_to_new[old_idx] = new_idx

        # zone_names
        chars = ",".join(f"'{c}'" for c in z["name"])
        new_zone_names_lines.append(
            f"    {chars},'\\\\0',{new_idx}, // zone {new_idx}"
        )
        out_bytes.extend(ord(c) for c in z["name"])
        out_bytes.append(0)
        out_bytes.append(new_idx)

        # zone_defns
        d = by_idx[old_idx]["data"]
        new_zone_defns_lines.append(
            f"{{ {d[0]},{d[1]},{d[2]},{new_idx} }},"
        )

    # ---------- Replace arrays ----------
    new_zone_names = (
        f"const unsigned char zone_names[{len(out_bytes)}] = {{\n"
        + "\n".join(new_zone_names_lines)
        + "\n};"
    )
    text = ZONE_NAMES_RE.sub(new_zone_names, text)

    new_zone_defns = (
        f"const uzone_packed_t zone_defns[{len(new_zone_defns_lines)}] = {{\n"
        + "\n".join(new_zone_defns_lines)
        + "\n};"
    )
    text = ZONE_DEFNS_RE.sub(new_zone_defns, text)

    with open(c_path, "w", encoding="utf-8") as f:
        f.write(text)

    print(
        f"zones.c updated: "
        f"{len(zone_defns)} → {len(deduped)} unique zones"
    )

    # ---------- Update zones.h ----------
    with open(h_path, "r", encoding="utf-8") as f:
        h_text = f.read()

    h_text = re.sub(
        r"#define NUM_ZONE_NAMES \d+",
        f"#define NUM_ZONE_NAMES {len(deduped)}",
        h_text
    )

    h_text = re.sub(
        r"extern const unsigned char zone_names\[\d+\]",
        f"extern const unsigned char zone_names[{len(out_bytes)}]",
        h_text
    )

    def repl_define(m):
        name, idx = m.groups()
        idx = int(idx)
        if idx in old_to_new:
            return f"#define {name} {old_to_new[idx]}"
        return f"/* {name} {idx} removed (duplicate behavior) */"

    h_text = UTZ_DEFINE_RE.sub(repl_define, h_text)

    with open(h_path, "w", encoding="utf-8") as f:
        f.write(h_text)

    print("zones.h updated")

if __name__ == "__main__":
    rewrite_zones("zones.c", "zones.h")
