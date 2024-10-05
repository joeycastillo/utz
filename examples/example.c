/** @file example.c
 *  @brief Simulates DST changeover on Sensor Watch
 *  @author Joey Castillo
 */

#include <stdio.h>
#include "utz.h"
#include "zones.h"
#include "utility.h"

int main() {
  printf("Total library db size: %lu B\n", sizeof(zone_rules) + sizeof(zone_abrevs) + sizeof(zone_defns) + sizeof(zone_names));

  uoffset_t offset;
  uzone_t utc_zone;
  watch_date_time system_time = {0};
  system_time.unit.year = 4;
  system_time.unit.month = 10;
  system_time.unit.day = 5;
  system_time.unit.hour = 14;
  system_time.unit.minute = 0;
  system_time.unit.second = 0;
  udatetime_t dt = {
    .date = {
      .year = UYEAR_FROM_YEAR(system_time.unit.year + WATCH_RTC_REFERENCE_YEAR),
      .month = system_time.unit.month,
      .dayofmonth = system_time.unit.day
    },
    .time = {
      .hour = system_time.unit.hour,
      .minute = system_time.unit.minute,
      .second = system_time.unit.second
    }
  };

  unpack_zone(&zone_defns[15], "", &utc_zone);
  get_current_offset(&utc_zone, &dt, &offset);
  printf("System zone: %s (offset %d:%02d)\n", utc_zone.abrev_formatter, offset.hours, offset.minutes);
  uzone_t local_zone;
  unpack_zone(&zone_defns[39], "", &local_zone);

  while (system_time.unit.hour != 19) {
    dt.date.year = UYEAR_FROM_YEAR(system_time.unit.year + WATCH_RTC_REFERENCE_YEAR);
    dt.date.month = system_time.unit.month;
    dt.date.dayofmonth = system_time.unit.day;
    dt.time.hour = system_time.unit.hour;
    dt.time.minute = system_time.unit.minute;
    dt.time.second = system_time.unit.second;

    
    printf("%02d:%02d:%02d %02d/%02d/%02d %s -> ", system_time.unit.hour, system_time.unit.minute, system_time.unit.second, system_time.unit.month, system_time.unit.day, WATCH_RTC_REFERENCE_YEAR + system_time.unit.year, utc_zone.abrev_formatter);
    watch_date_time local_time = watch_utility_date_time_convert_zone(system_time, 0, local_zone.offset.hours * 3600 + local_zone.offset.minutes * 60);
    printf("%02d:%02d:%02d %02d/%02d/%02d -> ", local_time.unit.hour, local_time.unit.minute, local_time.unit.second, local_time.unit.month, local_time.unit.day, WATCH_RTC_REFERENCE_YEAR + local_time.unit.year);

    dt.date.year = UYEAR_FROM_YEAR(local_time.unit.year + WATCH_RTC_REFERENCE_YEAR);
    dt.date.month = local_time.unit.month;
    dt.date.dayofmonth = local_time.unit.day;
    dt.time.hour = local_time.unit.hour;
    dt.time.minute = local_time.unit.minute;
    dt.time.second = local_time.unit.second;
    
    char c = get_current_offset(&local_zone, &dt, &offset);
    local_time = watch_utility_date_time_convert_zone(system_time, 0, offset.hours * 3600 + offset.minutes * 60);
    printf("%02d:%02d:%02d %02d/%02d/%02d ", local_time.unit.hour, local_time.unit.minute, local_time.unit.second, local_time.unit.month, local_time.unit.day, WATCH_RTC_REFERENCE_YEAR + local_time.unit.year);
    printf(local_zone.abrev_formatter, c);
    printf(" (offset: %d:%02d)\n", offset.hours, offset.minutes);

    system_time.unit.minute += 15;
    if (system_time.unit.minute >= 60) {
      system_time.unit.minute = 0;
      system_time.unit.hour++;
    }
    if (system_time.unit.hour >= 24) {
      system_time.unit.hour = 0;
      system_time.unit.day++;
    }
  }
}
