#include "utz.h"

#pragma once

extern const urule_packed_t zone_rules[20];
extern const char zone_abrevs[224];

#define MAX_ABREV_FORMATTER_LEN 11

extern const uzone_packed_t zone_defns[46];
#define UTZ_PAGO_PAGO      ( 0)
#define UTZ_HONOLULU       ( 1)
#define UTZ_ANCHORAGE      ( 2)
#define UTZ_LOS_ANGELES    ( 3)
#define UTZ_DENVER         ( 4)
#define UTZ_PHOENIX        ( 5)
#define UTZ_CHICAGO        ( 6)
#define UTZ_REGINA         ( 7)
#define UTZ_NEW_YORK       ( 8)
#define UTZ_HALIFAX        ( 9)
#define UTZ_MANAUS         (10)
#define UTZ_SANTIAGO       (11)
#define UTZ_SAO_PAULO      (12)
#define UTZ_ST_JOHNS       (13)
#define UTZ_NUUK           (14)
#define UTZ_UTC            (15)
#define UTZ_LONDON         (16)
#define UTZ_LAGOS          (17)
#define UTZ_BERLIN         (18)
#define UTZ_CAIRO          (19)
#define UTZ_MAPUTO         (20)
#define UTZ_JERUSALEM      (21)
#define UTZ_HELSINKI       (22)
#define UTZ_NAIROBI        (23)
#define UTZ_RIYADH         (24)
#define UTZ_MOSCOW         (25)
#define UTZ_TEHRAN         (26)
#define UTZ_DUBAI          (27)
#define UTZ_KOLKATA        (28)
#define UTZ_KATHMANDU      (29)
#define UTZ_YANGON         (30)
#define UTZ_BANGKOK        (31)
#define UTZ_SHANGHAI       (32)
#define UTZ_HONG_KONG      (33)
#define UTZ_SINGAPORE      (34)
#define UTZ_PERTH          (35)
#define UTZ_TOKYO          (36)
#define UTZ_SEOUL          (37)
#define UTZ_DARWIN         (38)
#define UTZ_ADELAIDE       (39)
#define UTZ_BRISBANE       (40)
#define UTZ_HOBART         (41)
#define UTZ_SYDNEY         (42)
#define UTZ_GUAM           (43)
#define UTZ_TARAWA         (44)
#define UTZ_AUCKLAND       (45)

#define NUM_ZONE_NAMES 46
#define MAX_ZONE_NAME_LEN 10

extern const unsigned char zone_names[506];
