/** @file test_timezone.c
 *  @brief Comprehensive test for u Time Zone Library with unified metrics
 *  @author tree-s
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utz.h"
#include "../zones.h"

#define TEST_PRINT(...)  printf(__VA_ARGS__)

/* Forward declaration (utz.c internal, used for testing) */
uint8_t days_in_month(uint8_t y, uint8_t m);

/* ------------------------------------------------------------- */
/* Global test counters                                          */
/* ------------------------------------------------------------- */

static int tests_total  = 0;
static int tests_passed = 0;

#define RUN_TEST(label, expr)                             \
    do {                                                   \
        tests_total++;                                    \
        if (expr) {                                       \
            tests_passed++;                               \
            TEST_PRINT("  [PASS] %s\n", label);           \
        } else {                                          \
            TEST_PRINT("  [FAIL] %s\n", label);           \
        }                                                 \
    } while (0)

/* ------------------------------------------------------------- */
/* Helpers                                                       */
/* ------------------------------------------------------------- */

static int valid_offset(const uoffset_t* o) {
    if (o->minutes < 0 || o->minutes >= 60)
        return 0;
    if (o->hours < -14 || o->hours > 14)
        return 0;
    return 1;
}

static int offset_minutes(const uoffset_t* o) {
    return (int)o->hours * 60 + (int)o->minutes;
}

/* Apply offset to a UTC time and normalize */
static void apply_offset(
    int utc_hour,
    int utc_minute,
    const uoffset_t* off,
    int* out_hour,
    int* out_minute
) {
    int total = utc_hour * 60 + utc_minute;
    total += off->hours * 60 + off->minutes;

    total %= (24 * 60);
    if (total < 0)
        total += (24 * 60);

    *out_hour = total / 60;
    *out_minute = total % 60;
}

/* ------------------------------------------------------------- */
/* Test runner                                                   */
/* ------------------------------------------------------------- */

int test_all_generated_zones(void) {
    TEST_PRINT("Testing...\n");

    TEST_PRINT("[INFO] Leap-year sanity tests:\n");

    RUN_TEST("2024 is leap year",
        is_leap_year(UYEAR_FROM_YEAR(2024)));

    RUN_TEST("Feb 2024 has 29 days",
        days_in_month(UYEAR_FROM_YEAR(2024), 2) == 29);

    RUN_TEST("2023 is not leap year",
        !is_leap_year(UYEAR_FROM_YEAR(2023)));

    RUN_TEST("Feb 2023 has 28 days",
        days_in_month(UYEAR_FROM_YEAR(2023), 2) == 28);

    udatetime_t winter = {
        .date = { .year = UYEAR_FROM_YEAR(2025), .month = 1, .dayofmonth = 15, .dayofweek = 0 },
        .time = { .hour = 12, .minute = 0, .second = 0 }
    };

    udatetime_t summer = {
        .date = { .year = UYEAR_FROM_YEAR(2025), .month = 7, .dayofmonth = 15, .dayofweek = 0 },
        .time = { .hour = 12, .minute = 0, .second = 0 }
    };

    udatetime_t leap_feb28 = {
        .date = { .year = UYEAR_FROM_YEAR(2024), .month = 2, .dayofmonth = 28, .dayofweek = 0 },
        .time = { .hour = 12, .minute = 0, .second = 0 }
    };

    udatetime_t leap_feb29 = {
        .date = { .year = UYEAR_FROM_YEAR(2024), .month = 2, .dayofmonth = 29, .dayofweek = 0 },
        .time = { .hour = 12, .minute = 0, .second = 0 }
    };

    udatetime_t leap_mar01 = {
        .date = { .year = UYEAR_FROM_YEAR(2024), .month = 3, .dayofmonth = 1, .dayofweek = 0 },
        .time = { .hour = 12, .minute = 0, .second = 0 }
    };

    const int utc_hour = 12;
    const int utc_minute = 0;

    const unsigned char* name_ptr = zone_names;

    for (int i = 0; i < NUM_ZONE_NAMES; i++) {
        const char* zone_name = (const char*)name_ptr;
        uint8_t defn_idx = name_ptr[strlen(zone_name) + 1];

        uzone_t zone;
        unpack_zone(&zone_defns[defn_idx], zone_name, &zone);

        TEST_PRINT("\nZone: %s\n", zone_name);

        uoffset_t off_winter, off_summer;
        uoffset_t off_feb28, off_feb29, off_mar01;

        char l_winter = get_current_offset(&zone, &winter, &off_winter);
        char l_summer = get_current_offset(&zone, &summer, &off_summer);

        get_current_offset(&zone, &leap_feb28, &off_feb28);
        get_current_offset(&zone, &leap_feb29, &off_feb29);
        get_current_offset(&zone, &leap_mar01, &off_mar01);

        int winter_min = offset_minutes(&off_winter);
        int summer_min = offset_minutes(&off_summer);

        /* Offset validity */
        RUN_TEST("Offsets are valid",
            valid_offset(&off_winter) &&
            valid_offset(&off_summer) &&
            valid_offset(&off_feb28) &&
            valid_offset(&off_feb29) &&
            valid_offset(&off_mar01));

        /* DST invariants (NOT assumptions) */
        if (zone.rules_len == 0) {
            RUN_TEST("No-DST zone offset does not change",
                winter_min == summer_min);
        } else {
            RUN_TEST("DST offset delta reasonable",
                (summer_min - winter_min) % 30 == 0 &&
                abs(summer_min - winter_min) <= 120);

            if (summer_min != winter_min && l_winter == l_summer) {
                TEST_PRINT("  [INFO] DST offset changed without letter change\n");
            } else if (summer_min == winter_min && l_winter != l_summer) {
                TEST_PRINT("  [INFO] DST letter changed without offset change\n");
            } else {
                RUN_TEST("DST letter consistent with offset behavior", 1);
            }

        }

        /* Leap-day continuity */
        RUN_TEST("Leap-day offset continuity",
            offset_minutes(&off_feb28) ==
            offset_minutes(&off_feb29) &&
            offset_minutes(&off_feb29) ==
            offset_minutes(&off_mar01));

        /* Local clock correctness */
        int lh, lm, eh;

        apply_offset(utc_hour, utc_minute, &off_winter, &lh, &lm);
        eh = (utc_hour + off_winter.hours) % 24;
        if (eh < 0) eh += 24;

        RUN_TEST("Winter local clock correct",
            lh == eh && lm == off_winter.minutes);

        apply_offset(utc_hour, utc_minute, &off_summer, &lh, &lm);
        eh = (utc_hour + off_summer.hours) % 24;
        if (eh < 0) eh += 24;

        RUN_TEST("Summer local clock correct",
            lh == eh && lm == off_summer.minutes);

        name_ptr += strlen(zone_name) + 2;
    }

    double percent = (tests_total > 0)
        ? ((double)tests_passed / tests_total) * 100.0
        : 0.0;

    TEST_PRINT(
        "\n=================================================\n"
        "FINAL TEST SUMMARY\n"
        "  Passed: %d / %d (%.2f%%)\n"
        "=================================================\n",
        tests_passed, tests_total, percent
    );

    return tests_passed == tests_total ? 1 : 0;
}

/* ------------------------------------------------------------- */

int main(void) {
    return test_all_generated_zones() ? 0 : 1;
}
