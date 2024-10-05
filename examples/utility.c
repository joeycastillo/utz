#include "utility.h"

#define LEAPOCH (946684800LL + 86400*(31+29))

#define DAYS_PER_400Y (365*400 + 97)
#define DAYS_PER_100Y (365*100 + 24)
#define DAYS_PER_4Y   (365*4   + 1)

// Function taken from `src/time/__year_to_secs.c` of musl libc
// https://musl.libc.org
static uint32_t __year_to_secs(uint32_t year, int *is_leap)
{
	if (year-2ULL <= 136) {
		int y = year;
		int leaps = (y-68)>>2;
		if (!((y-68)&3)) {
			leaps--;
			if (is_leap) *is_leap = 1;
		} else if (is_leap) *is_leap = 0;
		return 31536000*(y-70) + 86400*leaps;
	}

	int cycles, centuries, leaps, rem;

	if (!is_leap) is_leap = &(int){0};
	cycles = (year-100) / 400;
	rem = (year-100) % 400;
	if (rem < 0) {
		cycles--;
		rem += 400;
	}
	if (!rem) {
		*is_leap = 1;
		centuries = 0;
		leaps = 0;
	} else {
		if (rem >= 200) {
			if (rem >= 300) centuries = 3, rem -= 300;
			else centuries = 2, rem -= 200;
		} else {
			if (rem >= 100) centuries = 1, rem -= 100;
			else centuries = 0;
		}
		if (!rem) {
			*is_leap = 0;
			leaps = 0;
		} else {
			leaps = rem / 4U;
			rem %= 4U;
			*is_leap = !rem;
		}
	}

	leaps += 97*cycles + 24*centuries - *is_leap;

	return (year-100) * 31536000LL + leaps * 86400LL + 946684800 + 86400;
}

// Function taken from `src/time/__month_to_secs.c` of musl libc
// https://musl.libc.org
static int __month_to_secs(int month, int is_leap)
{
	static const int secs_through_month[] = {
		0, 31*86400, 59*86400, 90*86400,
		120*86400, 151*86400, 181*86400, 212*86400,
		243*86400, 273*86400, 304*86400, 334*86400 };
	int t = secs_through_month[month];
	if (is_leap && month >= 2) t+=86400;
	return t;
}

watch_date_time watch_utility_date_time_from_unix_time(uint32_t timestamp, int32_t utc_offset) {
    watch_date_time retval;
    retval.reg = 0;
    int32_t days, secs;
    int32_t remdays, remsecs, remyears;
    int32_t qc_cycles, c_cycles, q_cycles;
    int32_t years, months;
    int32_t wday, yday, leap;
    static const int8_t days_in_month[] = {31,30,31,30,31,31,30,31,30,31,31,29};
    timestamp += utc_offset;

    secs = timestamp - LEAPOCH;
    days = secs / 86400;
    remsecs = secs % 86400;
    if (remsecs < 0) {
        remsecs += 86400;
        days--;
    }

    wday = (3+days)%7;
    if (wday < 0) wday += 7;

    qc_cycles = (int)(days / DAYS_PER_400Y);
    remdays = days % DAYS_PER_400Y;
    if (remdays < 0) {
        remdays += DAYS_PER_400Y;
        qc_cycles--;
    }

    c_cycles = remdays / DAYS_PER_100Y;
    if (c_cycles == 4) c_cycles--;
    remdays -= c_cycles * DAYS_PER_100Y;

    q_cycles = remdays / DAYS_PER_4Y;
    if (q_cycles == 25) q_cycles--;
    remdays -= q_cycles * DAYS_PER_4Y;

    remyears = remdays / 365;
    if (remyears == 4) remyears--;
    remdays -= remyears * 365;

    leap = !remyears && (q_cycles || !c_cycles);
    yday = remdays + 31 + 28 + leap;
    if (yday >= 365+leap) yday -= 365+leap;

    years = remyears + 4*q_cycles + 100*c_cycles + 400*qc_cycles;

    for (months=0; days_in_month[months] <= remdays; months++)
        remdays -= days_in_month[months];

    years += 2000;

    months += 2;
    if (months >= 12) {
        months -=12;
        years++;
    }

    if (years < 2020 || years > 2083) return retval;
    retval.unit.year = years - WATCH_RTC_REFERENCE_YEAR;
    retval.unit.month = months + 1;
    retval.unit.day = remdays + 1;

    retval.unit.hour = remsecs / 3600;
    retval.unit.minute = remsecs / 60 % 60;
    retval.unit.second = remsecs % 60;

    return retval;
}

// Function adapted from `src/time/__tm_to_secs.c` of musl libc
// https://musl.libc.org
uint32_t watch_utility_convert_to_unix_time(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second, int32_t utc_offset) {
    int is_leap;

    // POSIX tm struct starts year at 1900 and month at 0
    // https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/time.h.html 
    uint32_t timestamp = __year_to_secs(year - 1900, &is_leap);
    timestamp += __month_to_secs(month - 1, is_leap);

    // Regular conversion from musl libc
    timestamp += (day - 1) * 86400;
    timestamp += hour * 3600;
    timestamp += minute * 60;
    timestamp += second;
    timestamp -= utc_offset;

    return timestamp;
}

uint32_t watch_utility_date_time_to_unix_time(watch_date_time date_time, int32_t utc_offset) {
    return watch_utility_convert_to_unix_time(date_time.unit.year + WATCH_RTC_REFERENCE_YEAR, date_time.unit.month, date_time.unit.day, date_time.unit.hour, date_time.unit.minute, date_time.unit.second, utc_offset);
}

watch_date_time watch_utility_date_time_convert_zone(watch_date_time date_time, uint32_t origin_utc_offset, uint32_t destination_utc_offset) {
    uint32_t timestamp = watch_utility_date_time_to_unix_time(date_time, origin_utc_offset);
    return watch_utility_date_time_from_unix_time(timestamp, destination_utc_offset);
}

