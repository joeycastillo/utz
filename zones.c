#include "zones.h"

const urule_packed_t zone_rules[20] = {
{  8, 255, 7,  1,  1,  2, 0, 1,  4, 0}, // 	AN	2008	max	-	Apr	Sun>=1	2:00s	0	S
{  8, 255, 7,  1,  1,  2, 0, 2, 10, 1}, // 	AN	2008	max	-	Oct	Sun>=1	2:00s	1:00	D
{  8, 255, 7,  1,  1,  2, 0, 1,  4, 0}, // 	AS	2008	max	-	Apr	Sun>=1	2:00s	0	S
{  8, 255, 7,  1,  1,  2, 0, 2, 10, 1}, // 	AS	2008	max	-	Oct	Sun>=1	2:00s	1:00	D
{  8, 255, 7,  1,  1,  2, 0, 1,  4, 0}, // 	AT	2008	max	-	Apr	Sun>=1	2:00s	0	S
{  1, 255, 7,  1,  1,  2, 0, 2, 10, 1}, // 	AT	2001	max	-	Oct	Sun>=1	2:00s	1:00	D
{  7, 255, 7,  8,  1,  2, 0, 2,  3, 1}, // 	Canada	2007	max	-	Mar	Sun>=8	2:00	1:00	D
{  7, 255, 7,  1,  1,  1, 0, 1, 11, 0}, // 	Canada	2007	max	-	Nov	Sun>=1	2:00	0	S
{ 19, 255, 7,  2,  0,  3, 0, 0,  4, 0}, // 	Chile	2019	max	-	Apr	Sun>=2	3:00u	0	-
{ 23, 255, 7,  2,  0,  4, 0, 0,  9, 1}, // 	Chile	2023	max	-	Sep	Sun>=2	4:00u	1:00	-
{  0, 255, 7,  0,  0,  1, 0, 1,  3, 1}, // 	EU	1981	max	-	Mar	lastSun	 1:00u	1:00	S
{  0, 255, 7,  0,  0,  1, 0, 0, 10, 0}, // 	EU	1996	max	-	Oct	lastSun	 1:00u	0	-
{ 23, 255, 5,  0,  1,  0, 0, 1,  4, 1}, // 	Egypt	2023	max	-	Apr	lastFri	 0:00	1:00	S
{ 23, 255, 4,  0,  1, 23, 0, 0, 10, 0}, // 	Egypt	2023	max	-	Oct	lastThu	24:00	0	-
{  8, 255, 7,  1,  1,  2, 0, 1,  4, 0}, // 	NZ	2008	max	-	Apr	Sun>=1	2:00s	0	S
{  7, 255, 7,  0,  1,  2, 0, 2,  9, 1}, // 	NZ	2007	max	-	Sep	lastSun	2:00s	1:00	D
{  7, 255, 7,  8,  1,  2, 0, 2,  3, 1}, // 	US	2007	max	-	Mar	Sun>=8	2:00	1:00	D
{  7, 255, 7,  1,  1,  1, 0, 1, 11, 0}, // 	US	2007	max	-	Nov	Sun>=1	2:00	0	S
{ 13, 255, 5, 23,  1,  2, 0, 2,  3, 1}, // 	Zion	2013	max	-	Mar	Fri>=23	2:00	1:00	D
{ 13, 255, 7,  0,  1,  1, 0, 1, 10, 0}, // 	Zion	2013	max	-	Oct	lastSun	2:00	0	S
};

const char zone_abrevs[224] = {
'S','S','T','\0',
'H','S','T','\0',
'A','K','%','c','T','\0',
'P','%','c','T','\0',
'M','%','c','T','\0',
'M','S','T','\0',
'C','%','c','T','\0',
'C','S','T','\0',
'E','%','c','T','\0',
'A','%','c','T','\0',
'-','0','4','\0',
'-','0','4','/','-','0','3','\0',
'-','0','3','/','-','0','2','\0',
'N','%','c','T','\0',
'-','0','2','/','-','0','1','\0',
'U','T','C','\0',
'G','M','T','/','B','S','T','\0',
'W','A','T','\0',
'C','E','%','c','T','\0',
'E','E','%','c','T','\0',
'C','A','T','\0',
'I','%','c','T','\0',
'E','A','T','\0',
'+','0','3','\0',
'M','S','K','\0',
'+','0','3','3','0','/','+','0','4','3','0','\0',
'+','0','4','\0',
'I','S','T','\0',
'+','0','5','4','5','\0',
'+','0','6','3','0','\0',
'+','0','7','\0',
'H','K','S','T','\0',
'+','0','8','\0',
'A','W','S','T','\0',
'J','S','T','\0',
'K','S','T','\0',
'A','C','S','T','\0',
'A','C','%','c','T','\0',
'A','E','S','T','\0',
'A','E','%','c','T','\0',
'C','h','S','T','\0',
'+','1','2','\0',
'N','Z','%','c','T','\0',
};

const uzone_packed_t zone_defns[46] = {
// Pacific/Pago_Pago	-11:00	-	SST
{-44,   0,   0,   0},
// Pacific/Honolulu	-10:00	-	HST
{-40,   0,   0,   4},
// America/Anchorage	-9:00	US	AK%sT
{-36,  16,   2,   8},
// America/Los_Angeles	-8:00	US	P%sT
{-32,  16,   2,  14},
// America/Denver	-7:00	US	M%sT
{-28,  16,   2,  19},
// America/Phoenix	-7:00	-	MST
{-28,   0,   0,  24},
// America/Chicago	-6:00	US	C%sT
{-24,  16,   2,  28},
// America/Regina	-6:00	-	CST
{-24,   0,   0,  33},
// America/New_York	-5:00	US	E%sT
{-20,  16,   2,  37},
// America/Halifax	-4:00	Canada	A%sT
{-16,   6,   2,  42},
// America/Manaus	-4:00	-	-04
{-16,   0,   0,  47},
// America/Santiago	-4:00	Chile	-04/-03
{-16,   8,   2,  51},
// America/Sao_Paulo	-3:00	Brazil	-03/-02
{-12,   0,   0,  59},
// America/St_Johns	-3:30	Canada	N%sT
{-10,   6,   2,  67},
// America/Nuuk	-2:00	EU	-02/-01
{ -8,  10,   2,  72},
// 	Etc/UTC		0	-	UTC
{  0,   0,   0,  80},
// Europe/London	0:00	EU	GMT/BST
{  0,  10,   2,  84},
// Africa/Lagos	1:00	-	WAT
{  4,   0,   0,  92},
// Europe/Berlin	1:00	EU	CE%sT
{  4,  10,   2,  96},
// Africa/Cairo	2:00	Egypt	EE%sT
{  8,  12,   2, 102},
// Africa/Maputo	2:00	-	CAT
{  8,   0,   0, 108},
// Asia/Jerusalem	2:00	Zion	I%sT
{  8,  18,   2, 112},
// Europe/Helsinki	2:00	EU	EE%sT
{  8,  10,   2, 102},
// Africa/Nairobi	3:00	-	EAT
{ 12,   0,   0, 117},
// Asia/Riyadh	3:00	-	+03
{ 12,   0,   0, 121},
// Europe/Moscow	3:00	-	MSK
{ 12,   0,   0, 125},
// Asia/Tehran	3:30	Iran	+0330/+0430
{ 14,   0,   0, 129},
// Asia/Dubai	4:00	-	+04
{ 16,   0,   0, 141},
// Asia/Kolkata	5:30	-	IST
{ 22,   0,   0, 145},
// Asia/Kathmandu	5:45	-	+0545
{ 23,   0,   0, 149},
// Asia/Yangon	6:30	-	+0630
{ 26,   0,   0, 155},
// Asia/Bangkok	7:00	-	+07
{ 28,   0,   0, 161},
// Asia/Shanghai	8:00	PRC	C%sT
{ 32,   0,   0,  33},
// Asia/Hong_Kong	8:00	HK	HK%sT
{ 32,   0,   0, 165},
// Asia/Singapore	8:00	-	+08
{ 32,   0,   0, 170},
// Australia/Perth	8:00	AW	AW%sT
{ 32,   0,   0, 174},
// Asia/Tokyo	9:00	Japan	J%sT
{ 36,   0,   0, 179},
// Asia/Seoul	9:00	ROK	K%sT
{ 36,   0,   0, 183},
// Australia/Darwin	9:30	Aus	AC%sT
{ 38,   0,   0, 187},
// Australia/Adelaide	9:30	AS	AC%sT
{ 38,   2,   2, 192},
// Australia/Brisbane	10:00	AQ	AE%sT
{ 40,   0,   0, 198},
// Australia/Hobart	10:00	AT	AE%sT
{ 40,   4,   2, 203},
// Australia/Sydney	10:00	AN	AE%sT
{ 40,   0,   2, 203},
// Pacific/Guam	10:00	-	ChST
{ 40,   0,   0, 209},
// Pacific/Tarawa	12:00	-	+12
{ 48,   0,   0, 214},
// Pacific/Auckland	12:00	NZ	NZ%sT
{ 48,  14,   2, 218},
};

const unsigned char zone_names[506] = {
               'P','O',' ','S','a','n','&','o','a','\0',   0, // Pago Pago
               'P','O',' ','h','N','L','U','L','U','\0',   1, // Honolulu
               'N','A',' ','A','n','c','h','r','g','\0',   2, // Anchorage
               'N','A',' ','S','e','a','t','t','L','\0',   3, // Los Angeles
               'N','A',' ','D','e','n','v','e','r','\0',   4, // Denver
               'N','A',' ','A','r','z','o','n','a','\0',   5, // Phoenix
               'N','A',' ','C','h','c','a','g','o','\0',   6, // Chicago
               'N','A',' ','R','e','g','i','n','a','\0',   7, // Regina
               'N','A',' ','N','Y','o','r','k',' ','\0',   8, // New York
               'N','A',' ','h','a','L','i','f','a','\0',   9, // Halifax
               'S','A',' ','n','&','n','a','U','s','\0',  10, // Manaus
               'S','A',' ','S','t','i','a','g','o','\0',  11, // Santiago
               'S','A',' ','S','a','o','P','L','o','\0',  12, // Sao Paulo
               'N','A',' ','S','t',' ','J','n','s','\0',  13, // St Johns
               'E','U','R',' ',' ','N','u','u','k','\0',  14, // Nuuk
               ' ',' ',' ',' ',' ',' ','U','t','C','\0',  15, // UTC
               'E','U','R',' ','L','o','n','d','n','\0',  16, // London
               'A','F','R',' ','L','a','g','o','s','\0',  17, // Lagos
               'E','U','R','B','e','r','L','I','N','\0',  18, // Berlin
               'M','E',' ','C','a','i','r','o',' ','\0',  19, // Cairo
               'A','F','R','n','&','a','p','t','o','\0',  20, // Maputo
               'M','E',' ','1','s','r','a','e','L','\0',  21, // Jerusalem
               'E','U','R','h','L','s','n','k','i','\0',  22, // Helsinki
               'A','F','R','N','a','i','r','o','b','\0',  23, // Nairobi
               'M','E',' ','R','y','a','d','h',' ','\0',  24, // Riyadh
               'R','U','S','n','&','s','c','o','u','\0',  25, // Moscow
               'M','E',' ','+','e','h','r','a','n','\0',  26, // Tehran
               'M','E',' ',' ','d','u','b','a','i','\0',  27, // Dubai
               ' ',' ',' ',' ','1','n','d','I','a','\0',  28, // Kolkata
               ' ',' ',' ',' ','N','e','p','a','L','\0',  29, // Kathmandu
               ' ',' ',' ','8','u','r','n','&','a','\0',  30, // Yangon
               ' ',' ',' ','B','n','g','k','O','k','\0',  31, // Bangkok
               ' ',' ',' ','S','h','n','g','h','i','\0',  32, // Shanghai
               ' ',' ',' ','h','o','n','K','o','n','\0',  33, // Hong Kong
               ' ',' ',' ','S','n','g','p','o','r','\0',  34, // Singapore
               'A','U','S',' ','P','e','r','t','h','\0',  35, // Perth
               ' ',' ',' ',' ','T','o','k','y','o','\0',  36, // Tokyo
               ' ',' ',' ','S','e','o','u','L',' ','\0',  37, // Seoul
               'A','U','S','D','a','r','u','i','n','\0',  38, // Darwin
               'A','U','S','A','d','L','a','i','d','\0',  39, // Adelaide
               'A','U','S','B','r','s','b','N','e','\0',  40, // Brisbane
               'A','U','S',' ','h','o','b','r','t','\0',  41, // Hobart
               'A','U','S','S','y','0','n','e','y','\0',  42, // Sydney
               'P','O',' ',' ','G','u','a','N','7','\0',  43, // Guam
               'P','O',' ','+','a','r','a','w','a','\0',  44, // Tarawa
               ' ',' ',' ','A','u','c','k','L','d','\0',  45, // Auckland
};
