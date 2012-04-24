/* ANSI-C code produced by gperf version 3.0.3 */
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
#error "gperf generated tables don't work with this execution character set. Please report a bug to <bug-gnu-gperf@gnu.org>."
#endif

#line 15 "fcd_param_names.gperf"

#include "libfcd.h"
#line 19 "fcd_param_names.gperf"
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
gperf_case_strncmp (register const char *s1, register const char *s2, register unsigned int n)
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
hashParamName (register const char *str, register unsigned int len)
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

struct paramNamePool_t
  {
    char paramNamePool_str14[sizeof("BAND")];
    char paramNamePool_str27[sizeof("BIAS_CURRENT")];
    char paramNamePool_str29[sizeof("BC_1")];
    char paramNamePool_str35[sizeof("IG6_P3_0DB")];
    char paramNamePool_str39[sizeof("LE_0")];
    char paramNamePool_str44[sizeof("BC_2")];
    char paramNamePool_str50[sizeof("IG4_P0_0DB")];
    char paramNamePool_str54[sizeof("BC_VUBAND")];
    char paramNamePool_str55[sizeof("IG4_P2_0DB")];
    char paramNamePool_str58[sizeof("LNA_GAIN")];
    char paramNamePool_str60[sizeof("IG5_P3_0DB")];
    char paramNamePool_str61[sizeof("B_LBAND\011\011\0110")];
    char paramNamePool_str62[sizeof("RF_BPF450MHZ")];
    char paramNamePool_str64[sizeof("LE_1")];
    char paramNamePool_str65[sizeof("IG1_N3_0DB")];
    char paramNamePool_str67[sizeof("RF_BPF840MHZ")];
    char paramNamePool_str70[sizeof("IG2_P3_0DB")];
    char paramNamePool_str73[sizeof("RF_BPF1590MHZ")];
    char paramNamePool_str74[sizeof("IG6_P6_0DB")];
    char paramNamePool_str75[sizeof("IG2_P0_0DB")];
    char paramNamePool_str78[sizeof("RF_BPF1560MHZ")];
    char paramNamePool_str79[sizeof("LE_2")];
    char paramNamePool_str80[sizeof("LG_P12_5DB")];
    char paramNamePool_str83[sizeof("RF_BPF1490MHZ")];
    char paramNamePool_str84[sizeof("LG_P0_0DB")];
    char paramNamePool_str85[sizeof("MG_P12_0DB")];
    char paramNamePool_str87[sizeof("RF_BPF540MHZ")];
    char paramNamePool_str88[sizeof("RF_BPF1460MHZ")];
    char paramNamePool_str89[sizeof("MG_P4_0DB")];
    char paramNamePool_str90[sizeof("LG_P10_0DB")];
    char paramNamePool_str92[sizeof("RF_LPF656MHZ")];
    char paramNamePool_str93[sizeof("BC_LBAND")];
    char paramNamePool_str94[sizeof("IG1_P6_0DB")];
    char paramNamePool_str95[sizeof("IF_4_30MHZ")];
    char paramNamePool_str97[sizeof("RF_BPF425MHZ")];
    char paramNamePool_str98[sizeof("RF_BPF1445MHZ")];
    char paramNamePool_str99[sizeof("IG5_P6_0DB")];
    char paramNamePool_str100[sizeof("IGM_SENSITIVITY")];
    char paramNamePool_str105[sizeof("LG_P20_0DB")];
    char paramNamePool_str107[sizeof("RF_BPF405MHZ")];
    char paramNamePool_str108[sizeof("RF_BPF1410MHZ")];
    char paramNamePool_str109[sizeof("IG2_P6_0DB")];
    char paramNamePool_str110[sizeof("IF_5_30MHZ")];
    char paramNamePool_str112[sizeof("RF_BPF615MHZ")];
    char paramNamePool_str114[sizeof("LG_P5_0DB")];
    char paramNamePool_str115[sizeof("IF_5_00MHZ")];
    char paramNamePool_str116[sizeof("LNA_ENHANCE")];
    char paramNamePool_str118[sizeof("RF_BPF1660MHZ")];
    char paramNamePool_str120[sizeof("IF_2_30MHZ")];
    char paramNamePool_str122[sizeof("RF_BPF505MHZ")];
    char paramNamePool_str123[sizeof("RF_BPF1680MHZ")];
    char paramNamePool_str124[sizeof("LG_N5_0DB")];
    char paramNamePool_str125[sizeof("MIXER_GAIN")];
    char paramNamePool_str127[sizeof("RF_LPF509MHZ")];
    char paramNamePool_str128[sizeof("RF_BPF1640MHZ")];
    char paramNamePool_str130[sizeof("IF_2_20MHZ")];
    char paramNamePool_str132[sizeof("RF_BPF970MHZ")];
    char paramNamePool_str134[sizeof("IF_4_60MHZ")];
    char paramNamePool_str135[sizeof("IF_4_40MHZ")];
    char paramNamePool_str137[sizeof("RF_BPF670MHZ")];
    char paramNamePool_str140[sizeof("IF_2_28MHZ")];
    char paramNamePool_str144[sizeof("IG6_P9_0DB")];
    char paramNamePool_str145[sizeof("IF_2_24MHZ")];
    char paramNamePool_str154[sizeof("LG_P2_5DB")];
    char paramNamePool_str158[sizeof("RF_BPF1700MHZ")];
    char paramNamePool_str159[sizeof("IF_2_60MHZ")];
    char paramNamePool_str160[sizeof("IF_2_40MHZ")];
    char paramNamePool_str164[sizeof("LG_N2_5DB")];
    char paramNamePool_str169[sizeof("IG5_P9_0DB")];
    char paramNamePool_str170[sizeof("LG_P15_0DB")];
    char paramNamePool_str172[sizeof("RF_LPF268MHZ")];
    char paramNamePool_str175[sizeof("IG4_P1_0DB")];
    char paramNamePool_str177[sizeof("RF_BPF475MHZ")];
    char paramNamePool_str179[sizeof("IG2_P9_0DB")];
    char paramNamePool_str182[sizeof("RF_BPF720MHZ")];
    char paramNamePool_str184[sizeof("MF_4_2MHZ")];
    char paramNamePool_str185[sizeof("LG_P25_0DB")];
    char paramNamePool_str186[sizeof("IG6_P15_0DB")];
    char paramNamePool_str188[sizeof("RF_BPF1750MHZ")];
    char paramNamePool_str190[sizeof("IF_2_45MHZ")];
    char paramNamePool_str192[sizeof("RF_BPF575MHZ")];
    char paramNamePool_str195[sizeof("IF_5_50MHZ")];
    char paramNamePool_str196[sizeof("IG6_P12_0DB")];
    char paramNamePool_str198[sizeof("RF_BPF1720MHZ")];
    char paramNamePool_str199[sizeof("MF_2_3MHZ")];
    char paramNamePool_str203[sizeof("RF_BPF1300MHZ")];
    char paramNamePool_str205[sizeof("IF_2_50MHZ")];
    char paramNamePool_str208[sizeof("RF_BPF1360MHZ")];
    char paramNamePool_str210[sizeof("IG3_P3_0DB")];
    char paramNamePool_str211[sizeof("IG5_P15_0DB")];
    char paramNamePool_str213[sizeof("MF_4_6MHZ")];
    char paramNamePool_str215[sizeof("IG3_P0_0DB")];
    char paramNamePool_str217[sizeof("RF_BPF760MHZ")];
    char paramNamePool_str218[sizeof("IF_GAIN5")];
    char paramNamePool_str219[sizeof("LE_3")];
    char paramNamePool_str221[sizeof("IG5_P12_0DB")];
    char paramNamePool_str223[sizeof("IF_GAIN2")];
    char paramNamePool_str225[sizeof("IF_4_10MHZ")];
    char paramNamePool_str228[sizeof("IF_GAIN4")];
    char paramNamePool_str229[sizeof("IF_2_90MHZ")];
    char paramNamePool_str230[sizeof("IF_4_80MHZ")];
    char paramNamePool_str234[sizeof("RF_FILTER")];
    char paramNamePool_str235[sizeof("IF_2_55MHZ")];
    char paramNamePool_str239[sizeof("IF_FILTER")];
    char paramNamePool_str241[sizeof("B_VHF3")];
    char paramNamePool_str243[sizeof("RF_BPF1320MHZ")];
    char paramNamePool_str244[sizeof("LG_P7_5DB")];
    char paramNamePool_str245[sizeof("LG_P30_0DB")];
    char paramNamePool_str248[sizeof("IF_GAIN1")];
    char paramNamePool_str249[sizeof("IG3_P6_0DB")];
    char paramNamePool_str250[sizeof("B_UHF")];
    char paramNamePool_str251[sizeof("B_VHF2")];
    char paramNamePool_str252[sizeof("IF_GAIN_MODE")];
    char paramNamePool_str253[sizeof("RF_BPF1530MHZ")];
    char paramNamePool_str255[sizeof("IF_2_80MHZ")];
    char paramNamePool_str258[sizeof("IF_GAIN6")];
    char paramNamePool_str259[sizeof("IF_2_95MHZ")];
    char paramNamePool_str260[sizeof("IF_3_30MHZ")];
    char paramNamePool_str265[sizeof("IF_3_00MHZ")];
    char paramNamePool_str266[sizeof("RF_BPF380MHZ")];
    char paramNamePool_str267[sizeof("RF_BPF360MHZ")];
    char paramNamePool_str270[sizeof("IF_3_20MHZ")];
    char paramNamePool_str275[sizeof("MF_27_0MHZ")];
    char paramNamePool_str280[sizeof("IF_2_15MHZ")];
    char paramNamePool_str282[sizeof("RF_BPF890MHZ")];
    char paramNamePool_str283[sizeof("IGM_LINEARITY")];
    char paramNamePool_str285[sizeof("IRF_9_0MHZ")];
    char paramNamePool_str286[sizeof("IRF_12_4MHZ")];
    char paramNamePool_str287[sizeof("IF_RC_FILTER")];
    char paramNamePool_str293[sizeof("MF_1_9MHZ")];
    char paramNamePool_str295[sizeof("LG_P17_5DB")];
    char paramNamePool_str299[sizeof("IF_3_60MHZ")];
    char paramNamePool_str300[sizeof("IF_3_40MHZ")];
    char paramNamePool_str305[sizeof("IRF_6_4MHZ")];
    char paramNamePool_str310[sizeof("IRF_1_0MHZ")];
    char paramNamePool_str311[sizeof("IRF_10_6MHZ")];
    char paramNamePool_str315[sizeof("IRF_4_4MHZ")];
    char paramNamePool_str319[sizeof("IG3_P9_0DB")];
    char paramNamePool_str320[sizeof("IRF_1_8MHZ")];
    char paramNamePool_str330[sizeof("IRF_2_6MHZ")];
    char paramNamePool_str344[sizeof("MF_3_0MHZ")];
    char paramNamePool_str345[sizeof("IF_2_70MHZ")];
    char paramNamePool_str347[sizeof("RF_LPF299MHZ")];
    char paramNamePool_str348[sizeof("IF_GAIN3")];
    char paramNamePool_str350[sizeof("IRF_1_2MHZ")];
    char paramNamePool_str369[sizeof("IF_3_90MHZ")];
    char paramNamePool_str372[sizeof("MIXER_FILTER")];
    char paramNamePool_str375[sizeof("IF_2_75MHZ")];
    char paramNamePool_str379[sizeof("MF_3_4MHZ")];
    char paramNamePool_str390[sizeof("IF_3_10MHZ")];
    char paramNamePool_str391[sizeof("IRF_14_7MHZ")];
    char paramNamePool_str395[sizeof("IF_3_80MHZ")];
    char paramNamePool_str421[sizeof("IRF_21_4MHZ")];
    char paramNamePool_str424[sizeof("MF_2_7MHZ")];
    char paramNamePool_str426[sizeof("IRF_21_0MHZ")];
    char paramNamePool_str466[sizeof("LE_OFF")];
    char paramNamePool_str474[sizeof("MF_3_8MHZ")];
    char paramNamePool_str480[sizeof("IRF_3_4MHZ")];
    char paramNamePool_str485[sizeof("IF_3_70MHZ")];
    char paramNamePool_str495[sizeof("IRF_5_3MHZ")];
    char paramNamePool_str531[sizeof("IRF_17_6MHZ")];
    char paramNamePool_str545[sizeof("IRF_7_7MHZ")];
  };
static const struct paramNamePool_t paramNamePool_contents =
  {
    "BAND",
    "BIAS_CURRENT",
    "BC_1",
    "IG6_P3_0DB",
    "LE_0",
    "BC_2",
    "IG4_P0_0DB",
    "BC_VUBAND",
    "IG4_P2_0DB",
    "LNA_GAIN",
    "IG5_P3_0DB",
    "B_LBAND\011\011\0110",
    "RF_BPF450MHZ",
    "LE_1",
    "IG1_N3_0DB",
    "RF_BPF840MHZ",
    "IG2_P3_0DB",
    "RF_BPF1590MHZ",
    "IG6_P6_0DB",
    "IG2_P0_0DB",
    "RF_BPF1560MHZ",
    "LE_2",
    "LG_P12_5DB",
    "RF_BPF1490MHZ",
    "LG_P0_0DB",
    "MG_P12_0DB",
    "RF_BPF540MHZ",
    "RF_BPF1460MHZ",
    "MG_P4_0DB",
    "LG_P10_0DB",
    "RF_LPF656MHZ",
    "BC_LBAND",
    "IG1_P6_0DB",
    "IF_4_30MHZ",
    "RF_BPF425MHZ",
    "RF_BPF1445MHZ",
    "IG5_P6_0DB",
    "IGM_SENSITIVITY",
    "LG_P20_0DB",
    "RF_BPF405MHZ",
    "RF_BPF1410MHZ",
    "IG2_P6_0DB",
    "IF_5_30MHZ",
    "RF_BPF615MHZ",
    "LG_P5_0DB",
    "IF_5_00MHZ",
    "LNA_ENHANCE",
    "RF_BPF1660MHZ",
    "IF_2_30MHZ",
    "RF_BPF505MHZ",
    "RF_BPF1680MHZ",
    "LG_N5_0DB",
    "MIXER_GAIN",
    "RF_LPF509MHZ",
    "RF_BPF1640MHZ",
    "IF_2_20MHZ",
    "RF_BPF970MHZ",
    "IF_4_60MHZ",
    "IF_4_40MHZ",
    "RF_BPF670MHZ",
    "IF_2_28MHZ",
    "IG6_P9_0DB",
    "IF_2_24MHZ",
    "LG_P2_5DB",
    "RF_BPF1700MHZ",
    "IF_2_60MHZ",
    "IF_2_40MHZ",
    "LG_N2_5DB",
    "IG5_P9_0DB",
    "LG_P15_0DB",
    "RF_LPF268MHZ",
    "IG4_P1_0DB",
    "RF_BPF475MHZ",
    "IG2_P9_0DB",
    "RF_BPF720MHZ",
    "MF_4_2MHZ",
    "LG_P25_0DB",
    "IG6_P15_0DB",
    "RF_BPF1750MHZ",
    "IF_2_45MHZ",
    "RF_BPF575MHZ",
    "IF_5_50MHZ",
    "IG6_P12_0DB",
    "RF_BPF1720MHZ",
    "MF_2_3MHZ",
    "RF_BPF1300MHZ",
    "IF_2_50MHZ",
    "RF_BPF1360MHZ",
    "IG3_P3_0DB",
    "IG5_P15_0DB",
    "MF_4_6MHZ",
    "IG3_P0_0DB",
    "RF_BPF760MHZ",
    "IF_GAIN5",
    "LE_3",
    "IG5_P12_0DB",
    "IF_GAIN2",
    "IF_4_10MHZ",
    "IF_GAIN4",
    "IF_2_90MHZ",
    "IF_4_80MHZ",
    "RF_FILTER",
    "IF_2_55MHZ",
    "IF_FILTER",
    "B_VHF3",
    "RF_BPF1320MHZ",
    "LG_P7_5DB",
    "LG_P30_0DB",
    "IF_GAIN1",
    "IG3_P6_0DB",
    "B_UHF",
    "B_VHF2",
    "IF_GAIN_MODE",
    "RF_BPF1530MHZ",
    "IF_2_80MHZ",
    "IF_GAIN6",
    "IF_2_95MHZ",
    "IF_3_30MHZ",
    "IF_3_00MHZ",
    "RF_BPF380MHZ",
    "RF_BPF360MHZ",
    "IF_3_20MHZ",
    "MF_27_0MHZ",
    "IF_2_15MHZ",
    "RF_BPF890MHZ",
    "IGM_LINEARITY",
    "IRF_9_0MHZ",
    "IRF_12_4MHZ",
    "IF_RC_FILTER",
    "MF_1_9MHZ",
    "LG_P17_5DB",
    "IF_3_60MHZ",
    "IF_3_40MHZ",
    "IRF_6_4MHZ",
    "IRF_1_0MHZ",
    "IRF_10_6MHZ",
    "IRF_4_4MHZ",
    "IG3_P9_0DB",
    "IRF_1_8MHZ",
    "IRF_2_6MHZ",
    "MF_3_0MHZ",
    "IF_2_70MHZ",
    "RF_LPF299MHZ",
    "IF_GAIN3",
    "IRF_1_2MHZ",
    "IF_3_90MHZ",
    "MIXER_FILTER",
    "IF_2_75MHZ",
    "MF_3_4MHZ",
    "IF_3_10MHZ",
    "IRF_14_7MHZ",
    "IF_3_80MHZ",
    "IRF_21_4MHZ",
    "MF_2_7MHZ",
    "IRF_21_0MHZ",
    "LE_OFF",
    "MF_3_8MHZ",
    "IRF_3_4MHZ",
    "IF_3_70MHZ",
    "IRF_5_3MHZ",
    "IRF_17_6MHZ",
    "IRF_7_7MHZ"
  };
#define paramNamePool ((const char *) &paramNamePool_contents)

static const struct FCDParamInfo_ paramNameTable[] =
  {
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
    {-1}, {-1}, {-1}, {-1}, {-1},
#line 45 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str14,			1, FCD_CMD_APP_GET_BAND,	 0},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
    {-1}, {-1}, {-1},
#line 96 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str27,		1, FCD_CMD_APP_GET_BIAS_CURRENT,	 0},
    {-1},
#line 98 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str29,			0, FCD_CMD_APP_GET_BIAS_CURRENT,	 1},
    {-1}, {-1}, {-1}, {-1}, {-1},
#line 198 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str35,		0, FCD_CMD_APP_GET_IF_GAIN6,	 0},
    {-1}, {-1}, {-1},
#line 40 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str39,			0, FCD_CMD_APP_GET_LNA_ENHANCE,	 1},
    {-1}, {-1}, {-1}, {-1},
#line 99 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str44,			0, FCD_CMD_APP_GET_BIAS_CURRENT,	 2},
    {-1}, {-1}, {-1}, {-1}, {-1},
#line 152 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str50,		0, FCD_CMD_APP_GET_IF_GAIN4,	 0},
    {-1}, {-1}, {-1},
#line 100 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str54,		0, FCD_CMD_APP_GET_BIAS_CURRENT,	 3},
#line 154 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str55,		0, FCD_CMD_APP_GET_IF_GAIN4,	 2},
    {-1}, {-1},
#line 23 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str58,		1, FCD_CMD_APP_GET_LNA_GAIN,	 0},
    {-1},
#line 191 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str60,		0, FCD_CMD_APP_GET_IF_GAIN5,	 0},
#line 49 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str61, FCD_CMD_APP_GET_BAND,	 3},
#line 62 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str62,		0, FCD_CMD_APP_GET_RF_FILTER,	 4},
    {-1},
#line 41 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str64,			0, FCD_CMD_APP_GET_LNA_ENHANCE,	 3},
#line 114 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str65,		0, FCD_CMD_APP_GET_IF_GAIN1,	 0},
    {-1},
#line 71 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str67,		0, FCD_CMD_APP_GET_RF_FILTER,	 13},
    {-1}, {-1},
#line 141 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str70,		0, FCD_CMD_APP_GET_IF_GAIN2,	 1},
    {-1}, {-1},
#line 84 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str73,		0, FCD_CMD_APP_GET_RF_FILTER,	 9},
#line 199 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str74,		0, FCD_CMD_APP_GET_IF_GAIN6,	 1},
#line 140 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str75,		0, FCD_CMD_APP_GET_IF_GAIN2,	 0},
    {-1}, {-1},
#line 83 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str78,		0, FCD_CMD_APP_GET_RF_FILTER,	 8},
#line 42 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str79,			0, FCD_CMD_APP_GET_LNA_ENHANCE,	 5},
#line 31 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str80,		0, FCD_CMD_APP_GET_LNA_GAIN,	 9},
    {-1}, {-1},
#line 81 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str83,		0, FCD_CMD_APP_GET_RF_FILTER,	 6},
#line 26 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str84,		0, FCD_CMD_APP_GET_LNA_GAIN,	 4},
#line 94 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str85,		0, FCD_CMD_APP_GET_MIXER_GAIN,	 1},
    {-1},
#line 65 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str87,		0, FCD_CMD_APP_GET_RF_FILTER,	 7},
#line 80 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str88,		0, FCD_CMD_APP_GET_RF_FILTER,	 5},
#line 93 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str89,		0, FCD_CMD_APP_GET_MIXER_GAIN,	 0},
#line 30 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str90,		0, FCD_CMD_APP_GET_LNA_GAIN,	 8},
    {-1},
#line 56 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str92,		0, FCD_CMD_APP_GET_RF_FILTER,	 8},
#line 97 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str93,		0, FCD_CMD_APP_GET_BIAS_CURRENT,	 0},
#line 115 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str94,		0, FCD_CMD_APP_GET_IF_GAIN1,	 1},
#line 163 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str95,		0, FCD_CMD_APP_GET_IF_FILTER,	 6},
    {-1},
#line 61 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str97,		0, FCD_CMD_APP_GET_RF_FILTER,	 3},
#line 79 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str98,		0, FCD_CMD_APP_GET_RF_FILTER,	 4},
#line 192 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str99,		0, FCD_CMD_APP_GET_IF_GAIN5,	 1},
#line 119 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str100,	0, FCD_CMD_APP_GET_IF_GAIN_MODE,	 1},
    {-1}, {-1}, {-1}, {-1},
#line 34 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str105,		0, FCD_CMD_APP_GET_LNA_GAIN,	 12},
    {-1},
#line 60 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str107,		0, FCD_CMD_APP_GET_RF_FILTER,	 2},
#line 78 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str108,		0, FCD_CMD_APP_GET_RF_FILTER,	 3},
#line 142 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str109,		0, FCD_CMD_APP_GET_IF_GAIN2,	 2},
#line 158 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str110,		0, FCD_CMD_APP_GET_IF_FILTER,	 1},
    {-1},
#line 67 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str112,		0, FCD_CMD_APP_GET_RF_FILTER,	 9},
    {-1},
#line 28 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str114,		0, FCD_CMD_APP_GET_LNA_GAIN,	 6},
#line 159 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str115,		0, FCD_CMD_APP_GET_IF_FILTER,	 2},
#line 38 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str116,		1, FCD_CMD_APP_GET_LNA_ENHANCE,	 0},
    {-1},
#line 86 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str118,		0, FCD_CMD_APP_GET_RF_FILTER,	 11},
    {-1},
#line 184 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str120,		0, FCD_CMD_APP_GET_IF_FILTER,	 27},
    {-1},
#line 64 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str122,		0, FCD_CMD_APP_GET_RF_FILTER,	 6},
#line 87 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str123,		0, FCD_CMD_APP_GET_RF_FILTER,	 12},
#line 24 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str124,		0, FCD_CMD_APP_GET_LNA_GAIN,	 0},
#line 92 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str125,		1, FCD_CMD_APP_GET_MIXER_GAIN,	 0},
    {-1},
#line 55 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str127,		0, FCD_CMD_APP_GET_RF_FILTER,	 0},
#line 85 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str128,		0, FCD_CMD_APP_GET_RF_FILTER,	 10},
    {-1},
#line 187 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str130,		0, FCD_CMD_APP_GET_IF_FILTER,	 30},
    {-1},
#line 73 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str132,		0, FCD_CMD_APP_GET_RF_FILTER,	 15},
    {-1},
#line 161 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str134,		0, FCD_CMD_APP_GET_IF_FILTER,	 4},
#line 162 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str135,		0, FCD_CMD_APP_GET_IF_FILTER,	 5},
    {-1},
#line 68 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str137,		0, FCD_CMD_APP_GET_RF_FILTER,	 10},
    {-1}, {-1},
#line 185 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str140,		0, FCD_CMD_APP_GET_IF_FILTER,	 28},
    {-1}, {-1}, {-1},
#line 200 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str144,		0, FCD_CMD_APP_GET_IF_GAIN6,	 2},
#line 186 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str145,		0, FCD_CMD_APP_GET_IF_FILTER,	 29},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 27 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str154,		0, FCD_CMD_APP_GET_LNA_GAIN,	 5},
    {-1}, {-1}, {-1},
#line 88 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str158,		0, FCD_CMD_APP_GET_RF_FILTER,	 13},
#line 179 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str159,		0, FCD_CMD_APP_GET_IF_FILTER,	 22},
#line 183 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str160,		0, FCD_CMD_APP_GET_IF_FILTER,	 26},
    {-1}, {-1}, {-1},
#line 25 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str164,		0, FCD_CMD_APP_GET_LNA_GAIN,	 1},
    {-1}, {-1}, {-1}, {-1},
#line 193 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str169,		0, FCD_CMD_APP_GET_IF_GAIN5,	 2},
#line 32 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str170,		0, FCD_CMD_APP_GET_LNA_GAIN,	 10},
    {-1},
#line 52 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str172,		0, FCD_CMD_APP_GET_RF_FILTER,	 0},
    {-1}, {-1},
#line 153 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str175,		0, FCD_CMD_APP_GET_IF_GAIN4,	 1},
    {-1},
#line 63 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str177,		0, FCD_CMD_APP_GET_RF_FILTER,	 5},
    {-1},
#line 143 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str179,		0, FCD_CMD_APP_GET_IF_GAIN2,	 3},
    {-1}, {-1},
#line 69 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str182,		0, FCD_CMD_APP_GET_RF_FILTER,	 11},
    {-1},
#line 105 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str184,		0, FCD_CMD_APP_GET_MIXER_FILTER,	 9},
#line 35 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str185,		0, FCD_CMD_APP_GET_LNA_GAIN,	 13},
#line 202 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str186,		0, FCD_CMD_APP_GET_IF_GAIN6,	 4},
    {-1},
#line 90 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str188,		0, FCD_CMD_APP_GET_RF_FILTER,	 15},
    {-1},
#line 182 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str190,		0, FCD_CMD_APP_GET_IF_FILTER,	 25},
    {-1},
#line 66 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str192,		0, FCD_CMD_APP_GET_RF_FILTER,	 8},
    {-1}, {-1},
#line 157 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str195,		0, FCD_CMD_APP_GET_IF_FILTER,	 0},
#line 201 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str196,		0, FCD_CMD_APP_GET_IF_GAIN6,	 3},
    {-1},
#line 89 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str198,		0, FCD_CMD_APP_GET_RF_FILTER,	 14},
#line 110 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str199,		0, FCD_CMD_APP_GET_MIXER_FILTER,	 14},
    {-1}, {-1}, {-1},
#line 75 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str203,		0, FCD_CMD_APP_GET_RF_FILTER,	 0},
    {-1},
#line 181 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str205,		0, FCD_CMD_APP_GET_IF_FILTER,	 24},
    {-1}, {-1},
#line 77 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str208,		0, FCD_CMD_APP_GET_RF_FILTER,	 2},
    {-1},
#line 147 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str210,		0, FCD_CMD_APP_GET_IF_GAIN3,	 1},
#line 195 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str211,		0, FCD_CMD_APP_GET_IF_GAIN5,	 4},
    {-1},
#line 104 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str213,		0, FCD_CMD_APP_GET_MIXER_FILTER,	 8},
    {-1},
#line 146 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str215,		0, FCD_CMD_APP_GET_IF_GAIN3,	 0},
    {-1},
#line 70 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str217,		0, FCD_CMD_APP_GET_RF_FILTER,	 12},
#line 190 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str218,		1, FCD_CMD_APP_GET_IF_GAIN5,	 0},
#line 43 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str219,			0, FCD_CMD_APP_GET_LNA_ENHANCE,	 7},
    {-1},
#line 194 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str221,		0, FCD_CMD_APP_GET_IF_GAIN5,	 3},
    {-1},
#line 139 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str223,		1, FCD_CMD_APP_GET_IF_GAIN2,	 0},
    {-1},
#line 164 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str225,		0, FCD_CMD_APP_GET_IF_FILTER,	 7},
    {-1}, {-1},
#line 151 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str228,		1, FCD_CMD_APP_GET_IF_GAIN4,	 0},
#line 175 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str229,		0, FCD_CMD_APP_GET_IF_FILTER,	 18},
#line 160 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str230,		0, FCD_CMD_APP_GET_IF_FILTER,	 3},
    {-1}, {-1}, {-1},
#line 51 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str234,		1, FCD_CMD_APP_GET_RF_FILTER,	 0},
#line 180 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str235,		0, FCD_CMD_APP_GET_IF_FILTER,	 23},
    {-1}, {-1}, {-1},
#line 156 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str239,		1, FCD_CMD_APP_GET_IF_FILTER,	 0},
    {-1},
#line 47 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str241,			0, FCD_CMD_APP_GET_BAND,	 1},
    {-1},
#line 76 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str243,		0, FCD_CMD_APP_GET_RF_FILTER,	 1},
#line 29 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str244,		0, FCD_CMD_APP_GET_LNA_GAIN,	 7},
#line 36 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str245,		0, FCD_CMD_APP_GET_LNA_GAIN,	 14},
    {-1}, {-1},
#line 113 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str248,		1, FCD_CMD_APP_GET_IF_GAIN1,	 0},
#line 148 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str249,		0, FCD_CMD_APP_GET_IF_GAIN3,	 2},
#line 48 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str250,			0, FCD_CMD_APP_GET_BAND,	 2},
#line 46 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str251,			0, FCD_CMD_APP_GET_BAND,	 0},
#line 117 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str252,		1, FCD_CMD_APP_GET_IF_GAIN_MODE,	 0},
#line 82 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str253,		0, FCD_CMD_APP_GET_RF_FILTER,	 7},
    {-1},
#line 176 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str255,		0, FCD_CMD_APP_GET_IF_FILTER,	 19},
    {-1}, {-1},
#line 197 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str258,		1, FCD_CMD_APP_GET_IF_GAIN6,	 0},
#line 174 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str259,		0, FCD_CMD_APP_GET_IF_FILTER,	 17},
#line 170 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str260,		0, FCD_CMD_APP_GET_IF_FILTER,	 13},
    {-1}, {-1}, {-1}, {-1},
#line 173 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str265,		0, FCD_CMD_APP_GET_IF_FILTER,	 16},
#line 59 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str266,		0, FCD_CMD_APP_GET_RF_FILTER,	 1},
#line 58 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str267,		0, FCD_CMD_APP_GET_RF_FILTER,	 0},
    {-1}, {-1},
#line 171 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str270,		0, FCD_CMD_APP_GET_IF_FILTER,	 14},
    {-1}, {-1}, {-1}, {-1},
#line 103 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str275,		0, FCD_CMD_APP_GET_MIXER_FILTER,	 0},
    {-1}, {-1}, {-1}, {-1},
#line 188 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str280,		0, FCD_CMD_APP_GET_IF_FILTER,	 31},
    {-1},
#line 72 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str282,		0, FCD_CMD_APP_GET_RF_FILTER,	 14},
#line 118 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str283,		0, FCD_CMD_APP_GET_IF_GAIN_MODE,	 0},
    {-1},
#line 128 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str285,		0, FCD_CMD_APP_GET_IF_RC_FILTER,	 6},
#line 126 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str286,		0, FCD_CMD_APP_GET_IF_RC_FILTER,	 4},
#line 121 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str287,		1, FCD_CMD_APP_GET_IF_RC_FILTER,	 0},
    {-1}, {-1}, {-1}, {-1}, {-1},
#line 111 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str293,		0, FCD_CMD_APP_GET_MIXER_FILTER,	 15},
    {-1},
#line 33 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str295,		0, FCD_CMD_APP_GET_LNA_GAIN,	 11},
    {-1}, {-1}, {-1},
#line 168 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str299,		0, FCD_CMD_APP_GET_IF_FILTER,	 11},
#line 169 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str300,		0, FCD_CMD_APP_GET_IF_FILTER,	 12},
    {-1}, {-1}, {-1}, {-1},
#line 130 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str305,		0, FCD_CMD_APP_GET_IF_RC_FILTER,	 8},
    {-1}, {-1}, {-1}, {-1},
#line 137 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str310,		0, FCD_CMD_APP_GET_IF_RC_FILTER,	 15},
#line 127 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str311,		0, FCD_CMD_APP_GET_IF_RC_FILTER,	 5},
    {-1}, {-1}, {-1},
#line 132 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str315,		0, FCD_CMD_APP_GET_IF_RC_FILTER,	 10},
    {-1}, {-1}, {-1},
#line 149 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str319,		0, FCD_CMD_APP_GET_IF_GAIN3,	 3},
#line 135 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str320,		0, FCD_CMD_APP_GET_IF_RC_FILTER,	 13},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 134 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str330,		0, FCD_CMD_APP_GET_IF_RC_FILTER,	 12},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
    {-1}, {-1}, {-1}, {-1},
#line 108 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str344,		0, FCD_CMD_APP_GET_MIXER_FILTER,	 12},
#line 178 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str345,		0, FCD_CMD_APP_GET_IF_FILTER,	 21},
    {-1},
#line 53 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str347,		0, FCD_CMD_APP_GET_RF_FILTER,	 8},
#line 145 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str348,		1, FCD_CMD_APP_GET_IF_GAIN3,	 0},
    {-1},
#line 136 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str350,		0, FCD_CMD_APP_GET_IF_RC_FILTER,	 14},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 165 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str369,		0, FCD_CMD_APP_GET_IF_FILTER,	 8},
    {-1}, {-1},
#line 102 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str372,		1, FCD_CMD_APP_GET_MIXER_FILTER,	 0},
    {-1}, {-1},
#line 177 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str375,		0, FCD_CMD_APP_GET_IF_FILTER,	 20},
    {-1}, {-1}, {-1},
#line 107 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str379,		0, FCD_CMD_APP_GET_MIXER_FILTER,	 11},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
    {-1},
#line 172 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str390,		0, FCD_CMD_APP_GET_IF_FILTER,	 15},
#line 125 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str391,		0, FCD_CMD_APP_GET_IF_RC_FILTER,	 3},
    {-1}, {-1}, {-1},
#line 166 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str395,		0, FCD_CMD_APP_GET_IF_FILTER,	 9},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 122 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str421,		0, FCD_CMD_APP_GET_IF_RC_FILTER,	 0},
    {-1}, {-1},
#line 109 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str424,		0, FCD_CMD_APP_GET_MIXER_FILTER,	 13},
    {-1},
#line 123 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str426,		0, FCD_CMD_APP_GET_IF_RC_FILTER,	 1},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
    {-1}, {-1}, {-1},
#line 39 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str466,			0, FCD_CMD_APP_GET_LNA_ENHANCE,	 0},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 106 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str474,		0, FCD_CMD_APP_GET_MIXER_FILTER,	 10},
    {-1}, {-1}, {-1}, {-1}, {-1},
#line 133 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str480,		0, FCD_CMD_APP_GET_IF_RC_FILTER,	 11},
    {-1}, {-1}, {-1}, {-1},
#line 167 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str485,		0, FCD_CMD_APP_GET_IF_FILTER,	 10},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 131 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str495,		0, FCD_CMD_APP_GET_IF_RC_FILTER,	 9},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 124 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str531,		0, FCD_CMD_APP_GET_IF_RC_FILTER,	 2},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
    {-1}, {-1}, {-1}, {-1},
#line 129 "fcd_param_names.gperf"
    {(int)(long)&((struct paramNamePool_t *)0)->paramNamePool_str545,		0, FCD_CMD_APP_GET_IF_RC_FILTER,	 7}
  };

#ifdef __GNUC__
__inline
#ifdef __GNUC_STDC_INLINE__
__attribute__ ((__gnu_inline__))
#endif
#endif
const struct FCDParamInfo_ *
lookupParamName (register const char *str, register unsigned int len)
{
  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      register int key = hashParamName (str, len);

      if (key <= MAX_HASH_VALUE && key >= 0)
        {
          register int o = paramNameTable[key].name;
          if (o >= 0)
            {
              register const char *s = o + paramNamePool;

              if ((((unsigned char)*str ^ (unsigned char)*s) & ~32) == 0 && !gperf_case_strncmp (str, s, len) && s[len] == '\0')
                return &paramNameTable[key];
            }
        }
    }
  return 0;
}
