#include "utz.h"

#pragma once

extern const urule_packed_t zone_rules[20];
extern const char zone_abrevs[224];

#define MAX_ABREV_FORMATTER_LEN 11

extern const uzone_packed_t zone_defns[46];
#define UTZ_PAGO_PAGO      &zone_defns[  0]
#define UTZ_HONOLULU       &zone_defns[  1]
#define UTZ_ANCHORAGE      &zone_defns[  2]
#define UTZ_LOS_ANGELES    &zone_defns[  3]
#define UTZ_DENVER         &zone_defns[  4]
#define UTZ_PHOENIX        &zone_defns[  5]
#define UTZ_CHICAGO        &zone_defns[  6]
#define UTZ_REGINA         &zone_defns[  7]
#define UTZ_NEW_YORK       &zone_defns[  8]
#define UTZ_HALIFAX        &zone_defns[  9]
#define UTZ_MANAUS         &zone_defns[ 10]
#define UTZ_SANTIAGO       &zone_defns[ 11]
#define UTZ_SAO_PAULO      &zone_defns[ 12]
#define UTZ_ST_JOHNS       &zone_defns[ 13]
#define UTZ_NUUK           &zone_defns[ 14]
#define UTZ_UTC            &zone_defns[ 15]
#define UTZ_LONDON         &zone_defns[ 16]
#define UTZ_LAGOS          &zone_defns[ 17]
#define UTZ_BERLIN         &zone_defns[ 18]
#define UTZ_CAIRO          &zone_defns[ 19]
#define UTZ_MAPUTO         &zone_defns[ 20]
#define UTZ_JERUSALEM      &zone_defns[ 21]
#define UTZ_HELSINKI       &zone_defns[ 22]
#define UTZ_NAIROBI        &zone_defns[ 23]
#define UTZ_RIYADH         &zone_defns[ 24]
#define UTZ_MOSCOW         &zone_defns[ 25]
#define UTZ_TEHRAN         &zone_defns[ 26]
#define UTZ_DUBAI          &zone_defns[ 27]
#define UTZ_KOLKATA        &zone_defns[ 28]
#define UTZ_KATHMANDU      &zone_defns[ 29]
#define UTZ_YANGON         &zone_defns[ 30]
#define UTZ_BANGKOK        &zone_defns[ 31]
#define UTZ_SHANGHAI       &zone_defns[ 32]
#define UTZ_HONG_KONG      &zone_defns[ 33]
#define UTZ_SINGAPORE      &zone_defns[ 34]
#define UTZ_PERTH          &zone_defns[ 35]
#define UTZ_TOKYO          &zone_defns[ 36]
#define UTZ_SEOUL          &zone_defns[ 37]
#define UTZ_DARWIN         &zone_defns[ 38]
#define UTZ_ADELAIDE       &zone_defns[ 39]
#define UTZ_BRISBANE       &zone_defns[ 40]
#define UTZ_HOBART         &zone_defns[ 41]
#define UTZ_SYDNEY         &zone_defns[ 42]
#define UTZ_GUAM           &zone_defns[ 43]
#define UTZ_TARAWA         &zone_defns[ 44]
#define UTZ_AUCKLAND       &zone_defns[ 45]

#define NUM_ZONE_NAMES 46
#define MAX_ZONE_NAME_LEN 10

extern const unsigned char zone_names[506];
