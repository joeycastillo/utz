#!/usr/bin/env python3

import os
import tarfile
import urllib.request

TZDATA_URL = "https://www.iana.org/time-zones/repository/tzdata-latest.tar.gz"


def download_tzdata(dest_dir: str):
    os.makedirs(dest_dir, exist_ok=True)

    archive_path = os.path.join(dest_dir, "tzdata-latest.tar.gz")

    print("Downloading latest tzdata...")

    req = urllib.request.Request(
        TZDATA_URL,
        headers={"User-Agent": "Mozilla/5.0"}
    )

    with urllib.request.urlopen(req) as resp, open(archive_path, "wb") as f:
        f.write(resp.read())

    print("Extracting tzdata...")
    with tarfile.open(archive_path, "r:gz") as tar:
        tar.extractall(path=dest_dir)

    print("Cleaning up archive...")
    os.remove(archive_path)

    print(f"tzdata extracted to: {os.path.abspath(dest_dir)}")


if __name__ == "__main__":
    import argparse

    parser = argparse.ArgumentParser(
        description="Download and extract latest IANA tzdata"
    )
    parser.add_argument(
        "output_dir",
        nargs="?",
        default="vendor/tzdata",
        help="Directory to extract tzdata into (default: ./vendor/tzdata)",
    )

    args = parser.parse_args()
    download_tzdata(args.output_dir)
