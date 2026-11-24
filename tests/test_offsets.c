/** @file test_offsets.c
 *  @brief Checks UTC offsets, mainly for negative zones that are not
 *         a whole number of hours (such as St. John's at UTC-3:30).
 *
 *  Build and run with: make test
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "utz.h"
#include "zones.h"

/* Offset in minutes for a zone on the 15th of the given month, at noon. */
static int offset_minutes(const uzone_packed_t* packed, uint8_t month) {
  uzone_t zone;
  uoffset_t offset;
  udatetime_t dt = {
    .date = { .year = UYEAR_FROM_YEAR(2026), .month = month, .dayofmonth = 15 },
    .time = { .hour = 12, .minute = 0, .second = 0 }
  };
  unpack_zone(packed, "", &zone);
  get_current_offset(&zone, &dt, &offset);
  return offset.hours * 60 + offset.minutes;
}

/* Writes minutes as an offset like "-3:30". */
static const char* hhmm(int minutes, char* buf) {
  sprintf(buf, "%c%d:%02d", minutes < 0 ? '-' : '+', abs(minutes) / 60, abs(minutes) % 60);
  return buf;
}

static void check(const char* name, int actual, int expected) {
  char a[8], e[8];
  printf("%-20s got %-6s expected %-6s %s\n", name, hhmm(actual, a), hhmm(expected, e),
         actual == expected ? "ok" : "FAIL");
  fflush(stdout);
  assert(actual == expected);
}

int main(void) {
  /* The bug: St. John's came out as about UTC+1:45 instead of UTC-3:30. */
  check("St. John's, January", offset_minutes(&zone_defns[UTZ_ST_JOHNS], 1), -210);
  check("St. John's, July",    offset_minutes(&zone_defns[UTZ_ST_JOHNS], 7), -150);

  /* unpack_zone itself, on a made-up UTC-9:30 zone with no DST rules.
     It should store -9 hours and -30 minutes, which add up to -9:30. */
  uzone_packed_t minus_930 = { .offset_inc_minutes = -38, .rules_idx = 0, .rules_len = 0, .abrev_formatter = 0 };
  uzone_t zone;
  unpack_zone(&minus_930, "", &zone);
  assert(zone.offset.hours == -9);
  assert(zone.offset.minutes == -30);
  check("Made-up -9:30 zone", zone.offset.hours * 60 + zone.offset.minutes, -570);

  /* A few ordinary zones, to show nothing else changed. */
  check("UTC",                 offset_minutes(&zone_defns[UTZ_UTC], 1), 0);
  check("New York, January",   offset_minutes(&zone_defns[UTZ_NEW_YORK], 1), -300);
  check("New York, July",      offset_minutes(&zone_defns[UTZ_NEW_YORK], 7), -240);
  check("Adelaide, January",   offset_minutes(&zone_defns[UTZ_ADELAIDE], 1), 630);
  check("Adelaide, July",      offset_minutes(&zone_defns[UTZ_ADELAIDE], 7), 570);

  printf("All tests passed.\n");
  return 0;
}
