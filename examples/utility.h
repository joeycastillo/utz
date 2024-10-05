#include <stdint.h>

typedef union {
    struct {
        uint32_t second : 6;    // 0-59
        uint32_t minute : 6;    // 0-59
        uint32_t hour : 5;      // 0-23
        uint32_t day : 5;       // 1-31
        uint32_t month : 4;     // 1-12
        uint32_t year : 6;      // 0-63 (representing 2020-2083)
    } unit;
    uint32_t reg;               // the bit-packed value as expected by the RTC peripheral's CLOCK register.
} rtc_date_time;

#define watch_date_time rtc_date_time

#define WATCH_RTC_REFERENCE_YEAR (2020)

watch_date_time watch_utility_date_time_from_unix_time(uint32_t timestamp, int32_t utc_offset);

uint32_t watch_utility_convert_to_unix_time(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second, int32_t utc_offset);

uint32_t watch_utility_date_time_to_unix_time(watch_date_time date_time, int32_t utc_offset);

watch_date_time watch_utility_date_time_convert_zone(watch_date_time date_time, uint32_t origin_utc_offset, uint32_t destination_utc_offset);
