#ifndef _ZONES_H
#define _ZONES_H

extern const urule_packed_t zone_rules[20];
extern const char zone_abrevs[162];

#define MAX_ABREV_FORMATTER_LEN 7

extern const uzone_packed_t zone_defns[47];
#define UTZ_CAIRO 21
#define UTZ_BRAZZAVILLE 17
#define UTZ_HARARE 19
#define UTZ_NAIROBI 23
#define UTZ_ANCHORAGE 2
#define UTZ_SAO_PAULO 12
#define UTZ_BUENOS_AIRES 12
#define UTZ_RIO_DE_JANEIRO 12
#define UTZ_BELO_HORIZONTE 12
#define UTZ_CHICAGO 7
#define UTZ_DALLASFORT_WORTH 7
#define UTZ_HOUSTON 7
#define UTZ_DENVER 5
#define UTZ_HALIFAX 10
#define UTZ_LOS_ANGELES 3
#define UTZ_TIJUANA 3
#define UTZ_SAN_FRANCISCO 3
#define UTZ_INLAND_EMPIRE 3
#define UTZ_MANAUS 9
#define UTZ_MEXICO_CITY 6
#define UTZ_REGINA 6
#define UTZ_GUADALAJARA 6
#define UTZ_NEW_YORK 8
#define UTZ_WASHINGTON_DC 8
#define UTZ_PHILADELPHIA 8
#define UTZ_MIAMI 8
#define UTZ_ATLANTA 8
#define UTZ_BOSTON 8
#define UTZ_GODTHAB 14
#define UTZ_PHOENIX 4
#define UTZ_SANTIAGO 11
#define UTZ_ST_JOHNS 13
#define UTZ_BANGKOK 30
#define UTZ_DUBAI 25
#define UTZ_HONG_KONG 31
#define UTZ_JERUSALEM 22
#define UTZ_KARACHI 26
#define UTZ_LAHORE 26
#define UTZ_KATMANDU 28
#define UTZ_KOLKATA 27
#define UTZ_CALCUTTA 27
#define UTZ_DELHI 27
#define UTZ_MUMBAI 27
#define UTZ_BANGALORE 27
#define UTZ_CHENNAI 27
#define UTZ_HYDERABAD 27
#define UTZ_AHMEDABAD 27
#define UTZ_PUNE 27
#define UTZ_SURAT 27
/* UTZ_ISTANBUL 24 removed (duplicate behavior) */
/* UTZ_KUWAIT 24 removed (duplicate behavior) */
/* UTZ_ANKARA 24 removed (duplicate behavior) */
#define UTZ_SEOUL 32
/* UTZ_SHANGHAI 26 removed (duplicate behavior) */
/* UTZ_TAIPEI 26 removed (duplicate behavior) */
/* UTZ_CHONGQING 26 removed (duplicate behavior) */
/* UTZ_GUANGZHOU 26 removed (duplicate behavior) */
/* UTZ_BEIJING 26 removed (duplicate behavior) */
/* UTZ_SHENZHEN 26 removed (duplicate behavior) */
/* UTZ_WUHAN 26 removed (duplicate behavior) */
/* UTZ_CHENGDU 26 removed (duplicate behavior) */
/* UTZ_TIANJIN 26 removed (duplicate behavior) */
/* UTZ_HANGZHOU 26 removed (duplicate behavior) */
/* UTZ_XIAN 26 removed (duplicate behavior) */
/* UTZ_CHANGZHOU 26 removed (duplicate behavior) */
/* UTZ_NANJING 26 removed (duplicate behavior) */
/* UTZ_JINAN 26 removed (duplicate behavior) */
/* UTZ_ZHENGZHOU 26 removed (duplicate behavior) */
/* UTZ_QINGDAO 26 removed (duplicate behavior) */
/* UTZ_SHENYANG 26 removed (duplicate behavior) */
/* UTZ_WENZHOU 26 removed (duplicate behavior) */
/* UTZ_NANCHANG 26 removed (duplicate behavior) */
/* UTZ_KUALA_LUMPUR 27 removed (duplicate behavior) */
#define UTZ_TEHRAN 24
/* UTZ_TOKYO 29 removed (duplicate behavior) */
/* UTZ_OSAKA 29 removed (duplicate behavior) */
/* UTZ_NAGOYA 29 removed (duplicate behavior) */
#define UTZ_RANGOON 29
#define UTZ_ADELAIDE 34
#define UTZ_BRISBANE 35
#define UTZ_DARWIN 33
#define UTZ_HOBART 37
/* UTZ_PERTH 35 removed (duplicate behavior) */
#define UTZ_SYDNEY 36
#define UTZ_UTC 15
#define UTZ_ATHENS 20
#define UTZ_HELSINKI 20
#define UTZ_BELGRADE 18
#define UTZ_BERLIN 18
#define UTZ_BRUSSELS 18
#define UTZ_MADRID 18
#define UTZ_ROME 18
#define UTZ_AMSTERDAM 18
#define UTZ_SARAJEVO 18
#define UTZ_RHINERUHR 18
#define UTZ_BARCELONA 18
#define UTZ_MUNICH 18
#define UTZ_STUTTGART 18
#define UTZ_HAMBURG 18
#define UTZ_MILAN 18
#define UTZ_LONDON 16
/* UTZ_MOSCOW 41 removed (duplicate behavior) */
#define UTZ_AUCKLAND 39
/* UTZ_GUAM 43 removed (duplicate behavior) */
#define UTZ_HONOLULU 1
#define UTZ_MIDWAY 0
#define UTZ_MAJURO 38

#define NUM_ZONE_NAMES 40
#define MAX_ZONE_NAME_LEN 17

extern const unsigned char zone_names[320];
#endif /* _ZONES_H */