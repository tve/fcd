/* C code produced by gperf version 3.0.3 */
/* Command-line: gperf fcd_param_names.gperf  */
/* Computed positions: -k'1,3-9' */

#if !((' ' == 32) && ('!' == 33) && ('"' == 34) && ('#' == 35) \
      && ('%' == 37) && ('&' == 38) && ('\'' == 39) && ('(' == 40) \
      && (')' == 41) && ('*' == 42) && ('+' == 43) && (',' == 44) \
      && ('-' == 45) && ('.' == 46) && ('/' == 47) && ('0' == 48) \
      && ('1' == 49) && ('2' == 50) && ('3' == 51) && ('4' == 52) \
      && ('5' == 53) && ('6' == 54) && ('7' == 55) && ('8' == 56) \
      && ('9' == 57) && (':' == 58) && (';' == 59) && ('<' == 60) \
      && ('=' == 61) && ('>' == 62) && ('?' == 63) && ('A' == 65) \
      && ('B' == 66) && ('C' == 67) && ('D' == 68) && ('E' == 69) \
      && ('F' == 70) && ('G' == 71) && ('H' == 72) && ('I' == 73) \
      && ('J' == 74) && ('K' == 75) && ('L' == 76) && ('M' == 77) \
      && ('N' == 78) && ('O' == 79) && ('P' == 80) && ('Q' == 81) \
      && ('R' == 82) && ('S' == 83) && ('T' == 84) && ('U' == 85) \
      && ('V' == 86) && ('W' == 87) && ('X' == 88) && ('Y' == 89) \
      && ('Z' == 90) && ('[' == 91) && ('\\' == 92) && (']' == 93) \
      && ('^' == 94) && ('_' == 95) && ('a' == 97) && ('b' == 98) \
      && ('c' == 99) && ('d' == 100) && ('e' == 101) && ('f' == 102) \
      && ('g' == 103) && ('h' == 104) && ('i' == 105) && ('j' == 106) \
      && ('k' == 107) && ('l' == 108) && ('m' == 109) && ('n' == 110) \
      && ('o' == 111) && ('p' == 112) && ('q' == 113) && ('r' == 114) \
      && ('s' == 115) && ('t' == 116) && ('u' == 117) && ('v' == 118) \
      && ('w' == 119) && ('x' == 120) && ('y' == 121) && ('z' == 122) \
      && ('{' == 123) && ('|' == 124) && ('}' == 125) && ('~' == 126))
/* The character set is not based on ISO-646.  */
error "gperf generated tables don't work with this execution character set. Please report a bug to <bug-gnu-gperf@gnu.org>."
#endif

#line 11 "fcd_param_names.gperf"

#include "libfcd.h"
#line 15 "fcd_param_names.gperf"
struct FCDParamInfo_;
enum
  {
    TOTAL_KEYWORDS = 162,
    MIN_WORD_LENGTH = 4,
    MAX_WORD_LENGTH = 15,
    MIN_HASH_VALUE = 14,
    MAX_HASH_VALUE = 545
  };

/* maximum key range = 532, duplicates = 0 */

#ifndef GPERF_DOWNCASE
#define GPERF_DOWNCASE 1
static unsigned char gperf_downcase[256] =
  {
      0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,
     15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,
     30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,
     45,  46,  47,  48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  58,  59,
     60,  61,  62,  63,  64,  97,  98,  99, 100, 101, 102, 103, 104, 105, 106,
    107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121,
    122,  91,  92,  93,  94,  95,  96,  97,  98,  99, 100, 101, 102, 103, 104,
    105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119,
    120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134,
    135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149,
    150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164,
    165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179,
    180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194,
    195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209,
    210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224,
    225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239,
    240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254,
    255
  };
#endif

#ifndef GPERF_CASE_STRNCMP
#define GPERF_CASE_STRNCMP 1
static int
gperf_case_strncmp (s1, s2, n)
     register const char *s1;
     register const char *s2;
     register unsigned int n;
{
  for (; n > 0;)
    {
      unsigned char c1 = gperf_downcase[(unsigned char)*s1++];
      unsigned char c2 = gperf_downcase[(unsigned char)*s2++];
      if (c1 != 0 && c1 == c2)
        {
          n--;
          continue;
        }
      return (int)c1 - (int)c2;
    }
  return 0;
}
#endif

#ifdef __GNUC__
__inline
#else
#ifdef __cplusplus
inline
#endif
#endif
static unsigned int
hashParamName (str, len)
     register const char *str;
     register unsigned int len;
{
  static const unsigned short asso_values[] =
    {
      546, 546, 546, 546, 546, 546, 546, 546, 546,   0,
      546, 546, 546,   0, 546, 546, 546, 546, 546, 546,
      546, 546, 546, 546, 546, 546, 546, 546, 546, 546,
      546, 546, 546, 546, 546, 546, 546, 546, 546, 546,
      546, 546, 546, 546, 546, 546, 546, 546,   0,  25,
       40, 180,  15,  30,   5, 130,  10,   0,  40,  85,
       39, 225, 135, 109, 546,   0,   0,   5,   0,   5,
      200,   5,  35,   5, 546,  20,  35,  25,  10, 190,
        0,  30,   0,   0,  15,  10,   0,  20,  65, 546,
       65, 546, 546, 546, 546,   0, 546,   0,   0,   5,
        0,   5, 200,   5,  35,   5, 546,  20,  35,  25,
       10, 190,   0,  30,   0,   0,  15,  10,   0,  20,
       65, 546,  65, 546, 546, 546, 546, 546, 546, 546,
      546, 546, 546, 546, 546, 546, 546, 546, 546, 546,
      546, 546, 546, 546, 546, 546, 546, 546, 546, 546,
      546, 546, 546, 546, 546, 546, 546, 546, 546, 546,
      546, 546, 546, 546, 546, 546, 546, 546, 546, 546,
      546, 546, 546, 546, 546, 546, 546, 546, 546, 546,
      546, 546, 546, 546, 546, 546, 546, 546, 546, 546,
      546, 546, 546, 546, 546, 546, 546, 546, 546, 546,
      546, 546, 546, 546, 546, 546, 546, 546, 546, 546,
      546, 546, 546, 546, 546, 546, 546, 546, 546, 546,
      546, 546, 546, 546, 546, 546, 546, 546, 546, 546,
      546, 546, 546, 546, 546, 546, 546, 546, 546, 546,
      546, 546, 546, 546, 546, 546, 546, 546, 546, 546,
      546, 546, 546, 546, 546, 546, 546, 546, 546, 546,
      546, 546
    };
  register int hval = len;

  switch (hval)
    {
      default:
        hval += asso_values[(unsigned char)str[8]];
      /*FALLTHROUGH*/
      case 8:
        hval += asso_values[(unsigned char)str[7]+4];
      /*FALLTHROUGH*/
      case 7:
        hval += asso_values[(unsigned char)str[6]];
      /*FALLTHROUGH*/
      case 6:
        hval += asso_values[(unsigned char)str[5]+6];
      /*FALLTHROUGH*/
      case 5:
        hval += asso_values[(unsigned char)str[4]];
      /*FALLTHROUGH*/
      case 4:
        hval += asso_values[(unsigned char)str[3]];
      /*FALLTHROUGH*/
      case 3:
        hval += asso_values[(unsigned char)str[2]];
      /*FALLTHROUGH*/
      case 2:
      case 1:
        hval += asso_values[(unsigned char)str[0]];
        break;
    }
  return hval;
}

static const struct FCDParamInfo_ paramNameTable[] =
  {
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""},
#line 40 "fcd_param_names.gperf"
    {"BAND",			'y', FCD_CMD_APP_GET_BAND,		 FCD_CMD_APP_SET_BAND,		 0},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""},
#line 91 "fcd_param_names.gperf"
    {"BIAS_CURRENT",		'y', FCD_CMD_APP_GET_BIAS_CURRENT,	 FCD_CMD_APP_SET_BIAS_CURRENT,	 0},
    {""},
#line 93 "fcd_param_names.gperf"
    {"BC_1",			'n', FCD_CMD_APP_GET_BIAS_CURRENT,	 FCD_CMD_APP_SET_BIAS_CURRENT,	 1},
    {""}, {""}, {""}, {""}, {""},
#line 193 "fcd_param_names.gperf"
    {"IG6_P3_0DB",		'n', FCD_CMD_APP_GET_IF_GAIN6,		 FCD_CMD_APP_SET_IF_GAIN6,	 0},
    {""}, {""}, {""},
#line 35 "fcd_param_names.gperf"
    {"LE_0",			'n', FCD_CMD_APP_GET_LNA_ENHANCE,	 FCD_CMD_APP_SET_LNA_ENHANCE,	 1},
    {""}, {""}, {""}, {""},
#line 94 "fcd_param_names.gperf"
    {"BC_2",			'n', FCD_CMD_APP_GET_BIAS_CURRENT,	 FCD_CMD_APP_SET_BIAS_CURRENT,	 2},
    {""}, {""}, {""}, {""}, {""},
#line 147 "fcd_param_names.gperf"
    {"IG4_P0_0DB",		'n', FCD_CMD_APP_GET_IF_GAIN4,		 FCD_CMD_APP_SET_IF_GAIN4,	 0},
    {""}, {""}, {""},
#line 95 "fcd_param_names.gperf"
    {"BC_VUBAND",		'n', FCD_CMD_APP_GET_BIAS_CURRENT,	 FCD_CMD_APP_SET_BIAS_CURRENT,	 3},
#line 149 "fcd_param_names.gperf"
    {"IG4_P2_0DB",		'n', FCD_CMD_APP_GET_IF_GAIN4,		 FCD_CMD_APP_SET_IF_GAIN4,	 2},
    {""}, {""},
#line 18 "fcd_param_names.gperf"
    {"LNA_GAIN",		'y', FCD_CMD_APP_GET_LNA_GAIN,		 FCD_CMD_APP_SET_LNA_GAIN,	 0},
    {""},
#line 186 "fcd_param_names.gperf"
    {"IG5_P3_0DB",		'n', FCD_CMD_APP_GET_IF_GAIN5,		 FCD_CMD_APP_SET_IF_GAIN5,	 0},
    {""},
#line 57 "fcd_param_names.gperf"
    {"RF_BPF450MHZ",		'n', FCD_CMD_APP_GET_RF_FILTER,		 FCD_CMD_APP_SET_RF_FILTER,	 4},
#line 44 "fcd_param_names.gperf"
    {"B_LBAND\011\011\011'n'", FCD_CMD_APP_GET_BAND,		 FCD_CMD_APP_SET_BAND,		 3},
#line 36 "fcd_param_names.gperf"
    {"LE_1",			'n', FCD_CMD_APP_GET_LNA_ENHANCE,	 FCD_CMD_APP_SET_LNA_ENHANCE,	 3},
#line 109 "fcd_param_names.gperf"
    {"IG1_N3_0DB",		'n', FCD_CMD_APP_GET_IF_GAIN1,		 FCD_CMD_APP_SET_IF_GAIN1,	 0},
    {""},
#line 66 "fcd_param_names.gperf"
    {"RF_BPF840MHZ",		'n', FCD_CMD_APP_GET_RF_FILTER,		 FCD_CMD_APP_SET_RF_FILTER,	 13},
    {""}, {""},
#line 136 "fcd_param_names.gperf"
    {"IG2_P3_0DB",		'n', FCD_CMD_APP_GET_IF_GAIN2,		 FCD_CMD_APP_SET_IF_GAIN2,	 1},
    {""}, {""},
#line 79 "fcd_param_names.gperf"
    {"RF_BPF1590MHZ",		'n', FCD_CMD_APP_GET_RF_FILTER,		 FCD_CMD_APP_SET_RF_FILTER,	 9},
#line 194 "fcd_param_names.gperf"
    {"IG6_P6_0DB",		'n', FCD_CMD_APP_GET_IF_GAIN6,		 FCD_CMD_APP_SET_IF_GAIN6,	 1},
#line 135 "fcd_param_names.gperf"
    {"IG2_P0_0DB",		'n', FCD_CMD_APP_GET_IF_GAIN2,		 FCD_CMD_APP_SET_IF_GAIN2,	 0},
    {""}, {""},
#line 78 "fcd_param_names.gperf"
    {"RF_BPF1560MHZ",		'n', FCD_CMD_APP_GET_RF_FILTER,		 FCD_CMD_APP_SET_RF_FILTER,	 8},
#line 37 "fcd_param_names.gperf"
    {"LE_2",			'n', FCD_CMD_APP_GET_LNA_ENHANCE,	 FCD_CMD_APP_SET_LNA_ENHANCE,	 5},
#line 26 "fcd_param_names.gperf"
    {"LG_P12_5DB",		'n', FCD_CMD_APP_GET_LNA_GAIN,		 FCD_CMD_APP_SET_LNA_GAIN,	 9},
    {""}, {""},
#line 76 "fcd_param_names.gperf"
    {"RF_BPF1490MHZ",		'n', FCD_CMD_APP_GET_RF_FILTER,		 FCD_CMD_APP_SET_RF_FILTER,	 6},
#line 21 "fcd_param_names.gperf"
    {"LG_P0_0DB",		'n', FCD_CMD_APP_GET_LNA_GAIN,		 FCD_CMD_APP_SET_LNA_GAIN,	 4},
#line 89 "fcd_param_names.gperf"
    {"MG_P12_0DB",		'n', FCD_CMD_APP_GET_MIXER_GAIN,	 FCD_CMD_APP_SET_MIXER_GAIN,	 1},
    {""},
#line 60 "fcd_param_names.gperf"
    {"RF_BPF540MHZ",		'n', FCD_CMD_APP_GET_RF_FILTER,		 FCD_CMD_APP_SET_RF_FILTER,	 7},
#line 75 "fcd_param_names.gperf"
    {"RF_BPF1460MHZ",		'n', FCD_CMD_APP_GET_RF_FILTER,		 FCD_CMD_APP_SET_RF_FILTER,	 5},
#line 88 "fcd_param_names.gperf"
    {"MG_P4_0DB",		'n', FCD_CMD_APP_GET_MIXER_GAIN,	 FCD_CMD_APP_SET_MIXER_GAIN,	 0},
#line 25 "fcd_param_names.gperf"
    {"LG_P10_0DB",		'n', FCD_CMD_APP_GET_LNA_GAIN,		 FCD_CMD_APP_SET_LNA_GAIN,	 8},
    {""},
#line 51 "fcd_param_names.gperf"
    {"RF_LPF656MHZ",		'n', FCD_CMD_APP_GET_RF_FILTER,		 FCD_CMD_APP_SET_RF_FILTER,	 8},
#line 92 "fcd_param_names.gperf"
    {"BC_LBAND",		'n', FCD_CMD_APP_GET_BIAS_CURRENT,	 FCD_CMD_APP_SET_BIAS_CURRENT,	 0},
#line 110 "fcd_param_names.gperf"
    {"IG1_P6_0DB",		'n', FCD_CMD_APP_GET_IF_GAIN1,		 FCD_CMD_APP_SET_IF_GAIN1,	 1},
#line 158 "fcd_param_names.gperf"
    {"IF_4_30MHZ",		'n', FCD_CMD_APP_GET_IF_FILTER,		 FCD_CMD_APP_SET_IF_FILTER,	 6},
    {""},
#line 56 "fcd_param_names.gperf"
    {"RF_BPF425MHZ",		'n', FCD_CMD_APP_GET_RF_FILTER,		 FCD_CMD_APP_SET_RF_FILTER,	 3},
#line 74 "fcd_param_names.gperf"
    {"RF_BPF1445MHZ",		'n', FCD_CMD_APP_GET_RF_FILTER,		 FCD_CMD_APP_SET_RF_FILTER,	 4},
#line 187 "fcd_param_names.gperf"
    {"IG5_P6_0DB",		'n', FCD_CMD_APP_GET_IF_GAIN5,		 FCD_CMD_APP_SET_IF_GAIN5,	 1},
#line 114 "fcd_param_names.gperf"
    {"IGM_SENSITIVITY",	'n', FCD_CMD_APP_GET_IF_GAIN_MODE,	 FCD_CMD_APP_SET_IF_GAIN_MODE,	 1},
    {""}, {""}, {""}, {""},
#line 29 "fcd_param_names.gperf"
    {"LG_P20_0DB",		'n', FCD_CMD_APP_GET_LNA_GAIN,		 FCD_CMD_APP_SET_LNA_GAIN,	 12},
    {""},
#line 55 "fcd_param_names.gperf"
    {"RF_BPF405MHZ",		'n', FCD_CMD_APP_GET_RF_FILTER,		 FCD_CMD_APP_SET_RF_FILTER,	 2},
#line 73 "fcd_param_names.gperf"
    {"RF_BPF1410MHZ",		'n', FCD_CMD_APP_GET_RF_FILTER,		 FCD_CMD_APP_SET_RF_FILTER,	 3},
#line 137 "fcd_param_names.gperf"
    {"IG2_P6_0DB",		'n', FCD_CMD_APP_GET_IF_GAIN2,		 FCD_CMD_APP_SET_IF_GAIN2,	 2},
#line 153 "fcd_param_names.gperf"
    {"IF_5_30MHZ",		'n', FCD_CMD_APP_GET_IF_FILTER,		 FCD_CMD_APP_SET_IF_FILTER,	 1},
    {""},
#line 62 "fcd_param_names.gperf"
    {"RF_BPF615MHZ",		'n', FCD_CMD_APP_GET_RF_FILTER,		 FCD_CMD_APP_SET_RF_FILTER,	 9},
    {""},
#line 23 "fcd_param_names.gperf"
    {"LG_P5_0DB",		'n', FCD_CMD_APP_GET_LNA_GAIN,		 FCD_CMD_APP_SET_LNA_GAIN,	 6},
#line 154 "fcd_param_names.gperf"
    {"IF_5_00MHZ",		'n', FCD_CMD_APP_GET_IF_FILTER,		 FCD_CMD_APP_SET_IF_FILTER,	 2},
#line 33 "fcd_param_names.gperf"
    {"LNA_ENHANCE",		'y', FCD_CMD_APP_GET_LNA_ENHANCE,	 FCD_CMD_APP_SET_LNA_ENHANCE,	 0},
    {""},
#line 81 "fcd_param_names.gperf"
    {"RF_BPF1660MHZ",		'n', FCD_CMD_APP_GET_RF_FILTER,		 FCD_CMD_APP_SET_RF_FILTER,	 11},
    {""},
#line 179 "fcd_param_names.gperf"
    {"IF_2_30MHZ",		'n', FCD_CMD_APP_GET_IF_FILTER,		 FCD_CMD_APP_SET_IF_FILTER,	 27},
    {""},
#line 59 "fcd_param_names.gperf"
    {"RF_BPF505MHZ",		'n', FCD_CMD_APP_GET_RF_FILTER,		 FCD_CMD_APP_SET_RF_FILTER,	 6},
#line 82 "fcd_param_names.gperf"
    {"RF_BPF1680MHZ",		'n', FCD_CMD_APP_GET_RF_FILTER,		 FCD_CMD_APP_SET_RF_FILTER,	 12},
#line 19 "fcd_param_names.gperf"
    {"LG_N5_0DB",		'n', FCD_CMD_APP_GET_LNA_GAIN,		 FCD_CMD_APP_SET_LNA_GAIN,	 0},
#line 87 "fcd_param_names.gperf"
    {"MIXER_GAIN",		'y', FCD_CMD_APP_GET_MIXER_GAIN,	 FCD_CMD_APP_SET_MIXER_GAIN,	 0},
    {""},
#line 50 "fcd_param_names.gperf"
    {"RF_LPF509MHZ",		'n', FCD_CMD_APP_GET_RF_FILTER,		 FCD_CMD_APP_SET_RF_FILTER,	 0},
#line 80 "fcd_param_names.gperf"
    {"RF_BPF1640MHZ",		'n', FCD_CMD_APP_GET_RF_FILTER,		 FCD_CMD_APP_SET_RF_FILTER,	 10},
    {""},
#line 182 "fcd_param_names.gperf"
    {"IF_2_20MHZ",		'n', FCD_CMD_APP_GET_IF_FILTER,		 FCD_CMD_APP_SET_IF_FILTER,	 30},
    {""},
#line 68 "fcd_param_names.gperf"
    {"RF_BPF970MHZ",		'n', FCD_CMD_APP_GET_RF_FILTER,		 FCD_CMD_APP_SET_RF_FILTER,	 15},
    {""},
#line 156 "fcd_param_names.gperf"
    {"IF_4_60MHZ",		'n', FCD_CMD_APP_GET_IF_FILTER,		 FCD_CMD_APP_SET_IF_FILTER,	 4},
#line 157 "fcd_param_names.gperf"
    {"IF_4_40MHZ",		'n', FCD_CMD_APP_GET_IF_FILTER,		 FCD_CMD_APP_SET_IF_FILTER,	 5},
    {""},
#line 63 "fcd_param_names.gperf"
    {"RF_BPF670MHZ",		'n', FCD_CMD_APP_GET_RF_FILTER,		 FCD_CMD_APP_SET_RF_FILTER,	 10},
    {""}, {""},
#line 180 "fcd_param_names.gperf"
    {"IF_2_28MHZ",		'n', FCD_CMD_APP_GET_IF_FILTER,		 FCD_CMD_APP_SET_IF_FILTER,	 28},
    {""}, {""}, {""},
#line 195 "fcd_param_names.gperf"
    {"IG6_P9_0DB",		'n', FCD_CMD_APP_GET_IF_GAIN6,		 FCD_CMD_APP_SET_IF_GAIN6,	 2},
#line 181 "fcd_param_names.gperf"
    {"IF_2_24MHZ",		'n', FCD_CMD_APP_GET_IF_FILTER,		 FCD_CMD_APP_SET_IF_FILTER,	 29},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 22 "fcd_param_names.gperf"
    {"LG_P2_5DB",		'n', FCD_CMD_APP_GET_LNA_GAIN,		 FCD_CMD_APP_SET_LNA_GAIN,	 5},
    {""}, {""}, {""},
#line 83 "fcd_param_names.gperf"
    {"RF_BPF1700MHZ",		'n', FCD_CMD_APP_GET_RF_FILTER,		 FCD_CMD_APP_SET_RF_FILTER,	 13},
#line 174 "fcd_param_names.gperf"
    {"IF_2_60MHZ",		'n', FCD_CMD_APP_GET_IF_FILTER,		 FCD_CMD_APP_SET_IF_FILTER,	 22},
#line 178 "fcd_param_names.gperf"
    {"IF_2_40MHZ",		'n', FCD_CMD_APP_GET_IF_FILTER,		 FCD_CMD_APP_SET_IF_FILTER,	 26},
    {""}, {""}, {""},
#line 20 "fcd_param_names.gperf"
    {"LG_N2_5DB",		'n', FCD_CMD_APP_GET_LNA_GAIN,		 FCD_CMD_APP_SET_LNA_GAIN,	 1},
    {""}, {""}, {""}, {""},
#line 188 "fcd_param_names.gperf"
    {"IG5_P9_0DB",		'n', FCD_CMD_APP_GET_IF_GAIN5,		 FCD_CMD_APP_SET_IF_GAIN5,	 2},
#line 27 "fcd_param_names.gperf"
    {"LG_P15_0DB",		'n', FCD_CMD_APP_GET_LNA_GAIN,		 FCD_CMD_APP_SET_LNA_GAIN,	 10},
    {""},
#line 47 "fcd_param_names.gperf"
    {"RF_LPF268MHZ",		'n', FCD_CMD_APP_GET_RF_FILTER,		 FCD_CMD_APP_SET_RF_FILTER,	 0},
    {""}, {""},
#line 148 "fcd_param_names.gperf"
    {"IG4_P1_0DB",		'n', FCD_CMD_APP_GET_IF_GAIN4,		 FCD_CMD_APP_SET_IF_GAIN4,	 1},
    {""},
#line 58 "fcd_param_names.gperf"
    {"RF_BPF475MHZ",		'n', FCD_CMD_APP_GET_RF_FILTER,		 FCD_CMD_APP_SET_RF_FILTER,	 5},
    {""},
#line 138 "fcd_param_names.gperf"
    {"IG2_P9_0DB",		'n', FCD_CMD_APP_GET_IF_GAIN2,		 FCD_CMD_APP_SET_IF_GAIN2,	 3},
    {""}, {""},
#line 64 "fcd_param_names.gperf"
    {"RF_BPF720MHZ",		'n', FCD_CMD_APP_GET_RF_FILTER,		 FCD_CMD_APP_SET_RF_FILTER,	 11},
    {""},
#line 100 "fcd_param_names.gperf"
    {"MF_4_2MHZ",		'n', FCD_CMD_APP_GET_MIXER_FILTER,	 FCD_CMD_APP_SET_MIXER_FILTER,	 9},
#line 30 "fcd_param_names.gperf"
    {"LG_P25_0DB",		'n', FCD_CMD_APP_GET_LNA_GAIN,		 FCD_CMD_APP_SET_LNA_GAIN,	 13},
#line 197 "fcd_param_names.gperf"
    {"IG6_P15_0DB",		'n', FCD_CMD_APP_GET_IF_GAIN6,		 FCD_CMD_APP_SET_IF_GAIN6,	 4},
    {""},
#line 85 "fcd_param_names.gperf"
    {"RF_BPF1750MHZ",		'n', FCD_CMD_APP_GET_RF_FILTER,		 FCD_CMD_APP_SET_RF_FILTER,	 15},
    {""},
#line 177 "fcd_param_names.gperf"
    {"IF_2_45MHZ",		'n', FCD_CMD_APP_GET_IF_FILTER,		 FCD_CMD_APP_SET_IF_FILTER,	 25},
    {""},
#line 61 "fcd_param_names.gperf"
    {"RF_BPF575MHZ",		'n', FCD_CMD_APP_GET_RF_FILTER,		 FCD_CMD_APP_SET_RF_FILTER,	 8},
    {""}, {""},
#line 152 "fcd_param_names.gperf"
    {"IF_5_50MHZ",		'n', FCD_CMD_APP_GET_IF_FILTER,		 FCD_CMD_APP_SET_IF_FILTER,	 0},
#line 196 "fcd_param_names.gperf"
    {"IG6_P12_0DB",		'n', FCD_CMD_APP_GET_IF_GAIN6,		 FCD_CMD_APP_SET_IF_GAIN6,	 3},
    {""},
#line 84 "fcd_param_names.gperf"
    {"RF_BPF1720MHZ",		'n', FCD_CMD_APP_GET_RF_FILTER,		 FCD_CMD_APP_SET_RF_FILTER,	 14},
#line 105 "fcd_param_names.gperf"
    {"MF_2_3MHZ",		'n', FCD_CMD_APP_GET_MIXER_FILTER,	 FCD_CMD_APP_SET_MIXER_FILTER,	 14},
    {""}, {""}, {""},
#line 70 "fcd_param_names.gperf"
    {"RF_BPF1300MHZ",		'n', FCD_CMD_APP_GET_RF_FILTER,		 FCD_CMD_APP_SET_RF_FILTER,	 0},
    {""},
#line 176 "fcd_param_names.gperf"
    {"IF_2_50MHZ",		'n', FCD_CMD_APP_GET_IF_FILTER,		 FCD_CMD_APP_SET_IF_FILTER,	 24},
    {""}, {""},
#line 72 "fcd_param_names.gperf"
    {"RF_BPF1360MHZ",		'n', FCD_CMD_APP_GET_RF_FILTER,		 FCD_CMD_APP_SET_RF_FILTER,	 2},
    {""},
#line 142 "fcd_param_names.gperf"
    {"IG3_P3_0DB",		'n', FCD_CMD_APP_GET_IF_GAIN3,		 FCD_CMD_APP_SET_IF_GAIN3,	 1},
#line 190 "fcd_param_names.gperf"
    {"IG5_P15_0DB",		'n', FCD_CMD_APP_GET_IF_GAIN5,		 FCD_CMD_APP_SET_IF_GAIN5,	 4},
    {""},
#line 99 "fcd_param_names.gperf"
    {"MF_4_6MHZ",		'n', FCD_CMD_APP_GET_MIXER_FILTER,	 FCD_CMD_APP_SET_MIXER_FILTER,	 8},
    {""},
#line 141 "fcd_param_names.gperf"
    {"IG3_P0_0DB",		'n', FCD_CMD_APP_GET_IF_GAIN3,		 FCD_CMD_APP_SET_IF_GAIN3,	 0},
    {""},
#line 65 "fcd_param_names.gperf"
    {"RF_BPF760MHZ",		'n', FCD_CMD_APP_GET_RF_FILTER,		 FCD_CMD_APP_SET_RF_FILTER,	 12},
#line 185 "fcd_param_names.gperf"
    {"IF_GAIN5",		'y', FCD_CMD_APP_GET_IF_GAIN5,		 FCD_CMD_APP_SET_IF_GAIN5,	 0},
#line 38 "fcd_param_names.gperf"
    {"LE_3",			'n', FCD_CMD_APP_GET_LNA_ENHANCE,	 FCD_CMD_APP_SET_LNA_ENHANCE,	 7},
    {""},
#line 189 "fcd_param_names.gperf"
    {"IG5_P12_0DB",		'n', FCD_CMD_APP_GET_IF_GAIN5,		 FCD_CMD_APP_SET_IF_GAIN5,	 3},
    {""},
#line 134 "fcd_param_names.gperf"
    {"IF_GAIN2",		'y', FCD_CMD_APP_GET_IF_GAIN2,		 FCD_CMD_APP_SET_IF_GAIN2,	 0},
    {""},
#line 159 "fcd_param_names.gperf"
    {"IF_4_10MHZ",		'n', FCD_CMD_APP_GET_IF_FILTER,		 FCD_CMD_APP_SET_IF_FILTER,	 7},
    {""}, {""},
#line 146 "fcd_param_names.gperf"
    {"IF_GAIN4",		'y', FCD_CMD_APP_GET_IF_GAIN4,		 FCD_CMD_APP_SET_IF_GAIN4,	 0},
#line 170 "fcd_param_names.gperf"
    {"IF_2_90MHZ",		'n', FCD_CMD_APP_GET_IF_FILTER,		 FCD_CMD_APP_SET_IF_FILTER,	 18},
#line 155 "fcd_param_names.gperf"
    {"IF_4_80MHZ",		'n', FCD_CMD_APP_GET_IF_FILTER,		 FCD_CMD_APP_SET_IF_FILTER,	 3},
    {""}, {""}, {""},
#line 46 "fcd_param_names.gperf"
    {"RF_FILTER",		'y', FCD_CMD_APP_GET_RF_FILTER,		 FCD_CMD_APP_SET_RF_FILTER,	 0},
#line 175 "fcd_param_names.gperf"
    {"IF_2_55MHZ",		'n', FCD_CMD_APP_GET_IF_FILTER,		 FCD_CMD_APP_SET_IF_FILTER,	 23},
    {""}, {""}, {""},
#line 151 "fcd_param_names.gperf"
    {"IF_FILTER",		'y', FCD_CMD_APP_GET_IF_FILTER,		 FCD_CMD_APP_SET_IF_FILTER,	 0},
    {""},
#line 42 "fcd_param_names.gperf"
    {"B_VHF3",			'n', FCD_CMD_APP_GET_BAND,		 FCD_CMD_APP_SET_BAND,		 1},
    {""},
#line 71 "fcd_param_names.gperf"
    {"RF_BPF1320MHZ",		'n', FCD_CMD_APP_GET_RF_FILTER,		 FCD_CMD_APP_SET_RF_FILTER,	 1},
#line 24 "fcd_param_names.gperf"
    {"LG_P7_5DB",		'n', FCD_CMD_APP_GET_LNA_GAIN,		 FCD_CMD_APP_SET_LNA_GAIN,	 7},
#line 31 "fcd_param_names.gperf"
    {"LG_P30_0DB",		'n', FCD_CMD_APP_GET_LNA_GAIN,		 FCD_CMD_APP_SET_LNA_GAIN,	 14},
    {""}, {""},
#line 108 "fcd_param_names.gperf"
    {"IF_GAIN1",		'y', FCD_CMD_APP_GET_IF_GAIN1,		 FCD_CMD_APP_SET_IF_GAIN1,	 0},
#line 143 "fcd_param_names.gperf"
    {"IG3_P6_0DB",		'n', FCD_CMD_APP_GET_IF_GAIN3,		 FCD_CMD_APP_SET_IF_GAIN3,	 2},
#line 43 "fcd_param_names.gperf"
    {"B_UHF",			'n', FCD_CMD_APP_GET_BAND,		 FCD_CMD_APP_SET_BAND,		 2},
#line 41 "fcd_param_names.gperf"
    {"B_VHF2",			'n', FCD_CMD_APP_GET_BAND,		 FCD_CMD_APP_SET_BAND,		 0},
#line 112 "fcd_param_names.gperf"
    {"IF_GAIN_MODE",		'y', FCD_CMD_APP_GET_IF_GAIN_MODE,	 FCD_CMD_APP_SET_IF_GAIN_MODE,	 0},
#line 77 "fcd_param_names.gperf"
    {"RF_BPF1530MHZ",		'n', FCD_CMD_APP_GET_RF_FILTER,		 FCD_CMD_APP_SET_RF_FILTER,	 7},
    {""},
#line 171 "fcd_param_names.gperf"
    {"IF_2_80MHZ",		'n', FCD_CMD_APP_GET_IF_FILTER,		 FCD_CMD_APP_SET_IF_FILTER,	 19},
    {""}, {""},
#line 192 "fcd_param_names.gperf"
    {"IF_GAIN6",		'y', FCD_CMD_APP_GET_IF_GAIN6,		 FCD_CMD_APP_SET_IF_GAIN6,	 0},
#line 169 "fcd_param_names.gperf"
    {"IF_2_95MHZ",		'n', FCD_CMD_APP_GET_IF_FILTER,		 FCD_CMD_APP_SET_IF_FILTER,	 17},
#line 165 "fcd_param_names.gperf"
    {"IF_3_30MHZ",		'n', FCD_CMD_APP_GET_IF_FILTER,		 FCD_CMD_APP_SET_IF_FILTER,	 13},
    {""}, {""}, {""}, {""},
#line 168 "fcd_param_names.gperf"
    {"IF_3_00MHZ",		'n', FCD_CMD_APP_GET_IF_FILTER,		 FCD_CMD_APP_SET_IF_FILTER,	 16},
#line 54 "fcd_param_names.gperf"
    {"RF_BPF380MHZ",		'n', FCD_CMD_APP_GET_RF_FILTER,		 FCD_CMD_APP_SET_RF_FILTER,	 1},
#line 53 "fcd_param_names.gperf"
    {"RF_BPF360MHZ",		'n', FCD_CMD_APP_GET_RF_FILTER,		 FCD_CMD_APP_SET_RF_FILTER,	 0},
    {""}, {""},
#line 166 "fcd_param_names.gperf"
    {"IF_3_20MHZ",		'n', FCD_CMD_APP_GET_IF_FILTER,		 FCD_CMD_APP_SET_IF_FILTER,	 14},
    {""}, {""}, {""}, {""},
#line 98 "fcd_param_names.gperf"
    {"MF_27_0MHZ",		'n', FCD_CMD_APP_GET_MIXER_FILTER,	 FCD_CMD_APP_SET_MIXER_FILTER,	 0},
    {""}, {""}, {""}, {""},
#line 183 "fcd_param_names.gperf"
    {"IF_2_15MHZ",		'n', FCD_CMD_APP_GET_IF_FILTER,		 FCD_CMD_APP_SET_IF_FILTER,	 31},
    {""},
#line 67 "fcd_param_names.gperf"
    {"RF_BPF890MHZ",		'n', FCD_CMD_APP_GET_RF_FILTER,		 FCD_CMD_APP_SET_RF_FILTER,	 14},
#line 113 "fcd_param_names.gperf"
    {"IGM_LINEARITY",		'n', FCD_CMD_APP_GET_IF_GAIN_MODE,	 FCD_CMD_APP_SET_IF_GAIN_MODE,	 0},
    {""},
#line 123 "fcd_param_names.gperf"
    {"IRF_9_0MHZ",		'n', FCD_CMD_APP_GET_IF_RC_FILTER,	 FCD_CMD_APP_SET_IF_RC_FILTER,	 6},
#line 121 "fcd_param_names.gperf"
    {"IRF_12_4MHZ",		'n', FCD_CMD_APP_GET_IF_RC_FILTER,	 FCD_CMD_APP_SET_IF_RC_FILTER,	 4},
#line 116 "fcd_param_names.gperf"
    {"IF_RC_FILTER",		'y', FCD_CMD_APP_GET_IF_RC_FILTER,	 FCD_CMD_APP_SET_IF_RC_FILTER,	 0},
    {""}, {""}, {""}, {""}, {""},
#line 106 "fcd_param_names.gperf"
    {"MF_1_9MHZ",		'n', FCD_CMD_APP_GET_MIXER_FILTER,	 FCD_CMD_APP_SET_MIXER_FILTER,	 15},
    {""},
#line 28 "fcd_param_names.gperf"
    {"LG_P17_5DB",		'n', FCD_CMD_APP_GET_LNA_GAIN,		 FCD_CMD_APP_SET_LNA_GAIN,	 11},
    {""}, {""}, {""},
#line 163 "fcd_param_names.gperf"
    {"IF_3_60MHZ",		'n', FCD_CMD_APP_GET_IF_FILTER,		 FCD_CMD_APP_SET_IF_FILTER,	 11},
#line 164 "fcd_param_names.gperf"
    {"IF_3_40MHZ",		'n', FCD_CMD_APP_GET_IF_FILTER,		 FCD_CMD_APP_SET_IF_FILTER,	 12},
    {""}, {""}, {""}, {""},
#line 125 "fcd_param_names.gperf"
    {"IRF_6_4MHZ",		'n', FCD_CMD_APP_GET_IF_RC_FILTER,	 FCD_CMD_APP_SET_IF_RC_FILTER,	 8},
    {""}, {""}, {""}, {""},
#line 132 "fcd_param_names.gperf"
    {"IRF_1_0MHZ",		'n', FCD_CMD_APP_GET_IF_RC_FILTER,	 FCD_CMD_APP_SET_IF_RC_FILTER,	 15},
#line 122 "fcd_param_names.gperf"
    {"IRF_10_6MHZ",		'n', FCD_CMD_APP_GET_IF_RC_FILTER,	 FCD_CMD_APP_SET_IF_RC_FILTER,	 5},
    {""}, {""}, {""},
#line 127 "fcd_param_names.gperf"
    {"IRF_4_4MHZ",		'n', FCD_CMD_APP_GET_IF_RC_FILTER,	 FCD_CMD_APP_SET_IF_RC_FILTER,	 10},
    {""}, {""}, {""},
#line 144 "fcd_param_names.gperf"
    {"IG3_P9_0DB",		'n', FCD_CMD_APP_GET_IF_GAIN3,		 FCD_CMD_APP_SET_IF_GAIN3,	 3},
#line 130 "fcd_param_names.gperf"
    {"IRF_1_8MHZ",		'n', FCD_CMD_APP_GET_IF_RC_FILTER,	 FCD_CMD_APP_SET_IF_RC_FILTER,	 13},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 129 "fcd_param_names.gperf"
    {"IRF_2_6MHZ",		'n', FCD_CMD_APP_GET_IF_RC_FILTER,	 FCD_CMD_APP_SET_IF_RC_FILTER,	 12},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""},
#line 103 "fcd_param_names.gperf"
    {"MF_3_0MHZ",		'n', FCD_CMD_APP_GET_MIXER_FILTER,	 FCD_CMD_APP_SET_MIXER_FILTER,	 12},
#line 173 "fcd_param_names.gperf"
    {"IF_2_70MHZ",		'n', FCD_CMD_APP_GET_IF_FILTER,		 FCD_CMD_APP_SET_IF_FILTER,	 21},
    {""},
#line 48 "fcd_param_names.gperf"
    {"RF_LPF299MHZ",		'n', FCD_CMD_APP_GET_RF_FILTER,		 FCD_CMD_APP_SET_RF_FILTER,	 8},
#line 140 "fcd_param_names.gperf"
    {"IF_GAIN3",		'y', FCD_CMD_APP_GET_IF_GAIN3,		 FCD_CMD_APP_SET_IF_GAIN3,	 0},
    {""},
#line 131 "fcd_param_names.gperf"
    {"IRF_1_2MHZ",		'n', FCD_CMD_APP_GET_IF_RC_FILTER,	 FCD_CMD_APP_SET_IF_RC_FILTER,	 14},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 160 "fcd_param_names.gperf"
    {"IF_3_90MHZ",		'n', FCD_CMD_APP_GET_IF_FILTER,		 FCD_CMD_APP_SET_IF_FILTER,	 8},
    {""}, {""},
#line 97 "fcd_param_names.gperf"
    {"MIXER_FILTER",		'y', FCD_CMD_APP_GET_MIXER_FILTER,	 FCD_CMD_APP_SET_MIXER_FILTER,	 0},
    {""}, {""},
#line 172 "fcd_param_names.gperf"
    {"IF_2_75MHZ",		'n', FCD_CMD_APP_GET_IF_FILTER,		 FCD_CMD_APP_SET_IF_FILTER,	 20},
    {""}, {""}, {""},
#line 102 "fcd_param_names.gperf"
    {"MF_3_4MHZ",		'n', FCD_CMD_APP_GET_MIXER_FILTER,	 FCD_CMD_APP_SET_MIXER_FILTER,	 11},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""},
#line 167 "fcd_param_names.gperf"
    {"IF_3_10MHZ",		'n', FCD_CMD_APP_GET_IF_FILTER,		 FCD_CMD_APP_SET_IF_FILTER,	 15},
#line 120 "fcd_param_names.gperf"
    {"IRF_14_7MHZ",		'n', FCD_CMD_APP_GET_IF_RC_FILTER,	 FCD_CMD_APP_SET_IF_RC_FILTER,	 3},
    {""}, {""}, {""},
#line 161 "fcd_param_names.gperf"
    {"IF_3_80MHZ",		'n', FCD_CMD_APP_GET_IF_FILTER,		 FCD_CMD_APP_SET_IF_FILTER,	 9},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 117 "fcd_param_names.gperf"
    {"IRF_21_4MHZ",		'n', FCD_CMD_APP_GET_IF_RC_FILTER,	 FCD_CMD_APP_SET_IF_RC_FILTER,	 0},
    {""}, {""},
#line 104 "fcd_param_names.gperf"
    {"MF_2_7MHZ",		'n', FCD_CMD_APP_GET_MIXER_FILTER,	 FCD_CMD_APP_SET_MIXER_FILTER,	 13},
    {""},
#line 118 "fcd_param_names.gperf"
    {"IRF_21_0MHZ",		'n', FCD_CMD_APP_GET_IF_RC_FILTER,	 FCD_CMD_APP_SET_IF_RC_FILTER,	 1},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""},
#line 34 "fcd_param_names.gperf"
    {"LE_OFF",			'n', FCD_CMD_APP_GET_LNA_ENHANCE,	 FCD_CMD_APP_SET_LNA_ENHANCE,	 0},
    {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 101 "fcd_param_names.gperf"
    {"MF_3_8MHZ",		'n', FCD_CMD_APP_GET_MIXER_FILTER,	 FCD_CMD_APP_SET_MIXER_FILTER,	 10},
    {""}, {""}, {""}, {""}, {""},
#line 128 "fcd_param_names.gperf"
    {"IRF_3_4MHZ",		'n', FCD_CMD_APP_GET_IF_RC_FILTER,	 FCD_CMD_APP_SET_IF_RC_FILTER,	 11},
    {""}, {""}, {""}, {""},
#line 162 "fcd_param_names.gperf"
    {"IF_3_70MHZ",		'n', FCD_CMD_APP_GET_IF_FILTER,		 FCD_CMD_APP_SET_IF_FILTER,	 10},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 126 "fcd_param_names.gperf"
    {"IRF_5_3MHZ",		'n', FCD_CMD_APP_GET_IF_RC_FILTER,	 FCD_CMD_APP_SET_IF_RC_FILTER,	 9},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 119 "fcd_param_names.gperf"
    {"IRF_17_6MHZ",		'n', FCD_CMD_APP_GET_IF_RC_FILTER,	 FCD_CMD_APP_SET_IF_RC_FILTER,	 2},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""},
#line 124 "fcd_param_names.gperf"
    {"IRF_7_7MHZ",		'n', FCD_CMD_APP_GET_IF_RC_FILTER,	 FCD_CMD_APP_SET_IF_RC_FILTER,	 7}
  };

#ifdef __GNUC__
__inline
#ifdef __GNUC_STDC_INLINE__
__attribute__ ((__gnu_inline__))
#endif
#endif
const struct FCDParamInfo_ *
lookupParamName (str, len)
     register const char *str;
     register unsigned int len;
{
  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      register int key = hashParamName (str, len);

      if (key <= MAX_HASH_VALUE && key >= 0)
        {
          register const char *s = paramNameTable[key].name;

          if ((((unsigned char)*str ^ (unsigned char)*s) & ~32) == 0 && !gperf_case_strncmp (str, s, len) && s[len] == '\0')
            return &paramNameTable[key];
        }
    }
  return 0;
}
