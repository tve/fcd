/***************************************************************************
 *  This file is part of libfcd
 * 
 *  Copyright (C) 2010  Howard Long, G6LVB
 *  Copyright (C) 2011  Alexandru Csete, OZ9AEC
 *                      Mario Lorenz, DL5MLO
 *  Copyright (C) 2012  John Brzustowski
 * 
 *  libfcd is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  libfcd is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with libfcd.  If not, see <http://www.gnu.org/licenses/>.
 *
 ***************************************************************************/

#ifndef LIBFCD_H
#define LIBFCD_H 1

#include <inttypes.h>
#include "libusb.h"

/** \brief FCD model enumeration. */
typedef enum {
  FCD_MODEL_PRO = 0,         /*!< FCD pro */
  FCD_MODEL_PRO_PLUS = 1,    /*!< FCD pro plus */

  FCD_MODEL_FIRST_MODEL = FCD_MODEL_PRO,
  FCD_MODEL_LAST_MODEL = FCD_MODEL_PRO_PLUS,
  FCD_MODEL_NUM_MODELS = FCD_MODEL_LAST_MODEL - FCD_MODEL_FIRST_MODEL + 1
} FCD_MODEL_ENUM; // The model type for a funcubedongle

extern const unsigned short _usVID[];
extern const unsigned short _usPID[];
extern char *FCD_MODEL_NAMES[];

/** \brief FCD USB interface number for getting/changing settings */
#define FCD_AUDIO_CONTROL_INTERFACE 0
#define FCD_STREAMING_INTERFACE 1
#define FCD_STREAMING_INTERFACE_SETTING_OFF 0
#define FCD_STREAMING_INTERFACE_SETTING_ON  1
#define FCD_SETTINGS_INTERFACE 2
#define FCD_SEND_COMMAND_ENDPOINT 0x02
#define FCD_RECEIVE_REPLY_ENDPOINT 0x82

/** \brief FCD device descriptor */
typedef struct {
  FCD_MODEL_ENUM	 model;		/*!< funcubedongle pro, pro+, ... */
  char			*pszModelName;	/*!< model name */
  libusb_device         *dev;           /*!< pointer to USB device; NULL means no device */
  libusb_device_handle	*phd;		/*!< handle of open device */
  uint8_t                busNum;        /*!< number USB bus on which device is found */
  uint8_t                devNum;        /*!< number of device on this USB bus */
  char			*pszPath;	/*!< system-dependent path to device */
} fcdDesc;

/** \brief FCD mode enumeration. */
typedef enum {
  FCD_MODE_BL,    /*!< FCD present in bootloader mode. */
  FCD_MODE_APP    /*!< FCD present in aplpication mode. */
} FCD_MODE_ENUM; // The current mode of the FCD: in bootloader mode or in normal application mode

/** \brief FCD return code enumeration. */
typedef enum {
  FCD_RETCODE_ABSENT = 1,  /*!< No FCD detected. */
  FCD_RETCODE_OKAY = 0,    /*!< FCD command succeeded */
  FCD_RETCODE_ERROR = 2    /*!< FCD command failed */
} FCD_RETCODE_ENUM;


#ifdef __cplusplus
extern "C" {
#endif

  /* Library functions */

  extern FCD_RETCODE_ENUM fcdInitLibrary();
  extern FCD_RETCODE_ENUM fcdShutDownLibrary();

  /* Application functions */

  extern FCD_RETCODE_ENUM fcdOpen(fcdDesc *fcd, uint16_t enumNum, uint8_t busNum, uint8_t devNum, uint16_t bcdDevice);
  extern FCD_RETCODE_ENUM fcdResetDev(uint16_t enumNum, uint8_t busNum, uint8_t devNum);
  extern FCD_RETCODE_ENUM fcdClose(fcdDesc *fcd);
  extern FCD_RETCODE_ENUM fcdGetMode(fcdDesc *fcd, FCD_MODE_ENUM *pMode);
  extern FCD_RETCODE_ENUM fcdGetFwVerStr(fcdDesc *fcd, char *str);
  extern FCD_RETCODE_ENUM fcdAppReset(fcdDesc *fcd);
  extern FCD_RETCODE_ENUM fcdAppSetFreqkHz(fcdDesc *fcd, int nFreq);
  extern FCD_RETCODE_ENUM fcdAppSetFreq(fcdDesc *fcd, uint32_t nFreq, uint32_t * actualFreq);
  extern FCD_RETCODE_ENUM fcdAppGetFreq(fcdDesc *fcd, uint32_t *nFreq);
  
  extern FCD_RETCODE_ENUM fcdAppSetParam(fcdDesc *fcd, uint8_t u8Cmd, uint8_t *pu8Data, uint8_t u8len);
  extern FCD_RETCODE_ENUM fcdAppGetParam(fcdDesc *fcd, uint8_t u8Cmd, uint8_t *pu8Data, uint8_t u8len);
  
  extern FCD_RETCODE_ENUM fcdAppSetParamDefaults(fcdDesc *fcd);

  /* Bootloader functions */
  extern FCD_RETCODE_ENUM fcdBlReset(fcdDesc *fcd);
  extern FCD_RETCODE_ENUM fcdBlErase(fcdDesc *fcd);
  extern FCD_RETCODE_ENUM fcdBlWriteFirmware(fcdDesc *fcd, unsigned char *pc, int n, uint32_t start, uint32_t end);
  extern FCD_RETCODE_ENUM fcdBlVerifyFirmware(fcdDesc *fcd, unsigned char *pc, int n, uint32_t start, uint32_t end);
  extern FCD_RETCODE_ENUM fcdBlGetByteAddrRange(fcdDesc *fcd, uint32_t *start, uint32_t *end);
  extern FCD_RETCODE_ENUM fcdBlSetByteAddr(fcdDesc *fcd, uint32_t start);
  extern FCD_RETCODE_ENUM fcdBlErase(fcdDesc *fcd);

#ifdef __cplusplus
}
#endif


/* Commands applicable in bootloader mode */
#define FCD_CMD_BL_QUERY                1  /*!< Returns string with "FCDAPP version". */
#define FCD_CMD_BL_RESET                8  /*!< Reset to application mode. */
#define FCD_CMD_BL_ERASE               24  /*!< Erase firmware from FCD flash. */
#define FCD_CMD_BL_SET_BYTE_ADDR       25  /*!< TBD */
#define FCD_CMD_BL_GET_BYTE_ADDR_RANGE 26  /*!< Get address range. */
#define FCD_CMD_BL_WRITE_FLASH_BLOCK   27  /*!< Write flash block. */
#define FCD_CMD_BL_READ_FLASH_BLOCK    28  /*!< Read flash block. */

/* Commands applicable in application mode */
#define FCD_CMD_APP_SET_FREQ_KHZ     100 /*!< Send with 3 byte unsigned little endian frequency in kHz. */
#define FCD_CMD_APP_SET_FREQ_HZ      101 /*!< Send with 4 byte unsigned little endian frequency in Hz, returns wit actual frequency set in Hz */
#define FCD_CMD_APP_GET_FREQ_HZ      102 /*!< Returns 4 byte unsigned little endian frequency in Hz. */

#define FCD_CMD_APP_GET_IF_RSSI      104 /*!< Returns 1 byte unsigned IF RSSI, -35dBm ~=0, -10dBm ~=70. */
#define FCD_CMD_APP_GET_PLL_LOCK     105 /*!< Returns 1 bit, true if locked. */

#define FCD_CMD_APP_SET_DC_CORR      106 /*!< Send with 2 byte unsigned I DC correction followed by 2 byte unsigned Q DC correction. 32768 is the default centre value. */
#define FCD_CMD_APP_GET_DC_CORR      107 /*!< Returns 2 byte unsigned I DC correction followed by 2 byte unsigned Q DC correction. 32768 is the default centre value. */
#define FCD_CMD_APP_SET_IQ_CORR      108 /*!< Send with 2 byte signed phase correction followed by 2 byte unsigned gain correction. 0 is the default centre value for phase correction, 32768 is the default centre value for gain. */
#define FCD_CMD_APP_GET_IQ_CORR      109 /*!< Returns 2 byte signed phase correction followed by 2 byte unsigned gain correction. 0 is the default centre value for phase correction, 32768 is the default centre value for gain. */

#define FCD_CMD_APP_FIRST_SET_CMD    110
#define FCD_CMD_APP_SET_LNA_GAIN     110 /*!< Send a 1 byte value, see enums for reference. */
#define FCD_CMD_APP_SET_LNA_ENHANCE  111
#define FCD_CMD_APP_SET_BAND         112
#define FCD_CMD_APP_SET_RF_FILTER    113
#define FCD_CMD_APP_SET_MIXER_GAIN   114
#define FCD_CMD_APP_SET_BIAS_CURRENT 115
#define FCD_CMD_APP_SET_MIXER_FILTER 116
#define FCD_CMD_APP_SET_IF_GAIN1     117
#define FCD_CMD_APP_SET_IF_GAIN_MODE 118
#define FCD_CMD_APP_SET_IF_RC_FILTER 119
#define FCD_CMD_APP_SET_IF_GAIN2     120
#define FCD_CMD_APP_SET_IF_GAIN3     121
#define FCD_CMD_APP_SET_IF_FILTER    122
#define FCD_CMD_APP_SET_IF_GAIN4     123
#define FCD_CMD_APP_SET_IF_GAIN5     124
#define FCD_CMD_APP_SET_IF_GAIN6     125
#define FCD_CMD_APP_SET_BIAS_TEE     126
#define FCD_CMD_APP_NUM_PARAMS       (FCD_CMD_APP_SET_BIAS_TEE - FCD_CMD_APP_FIRST_SET_CMD + 1)

#define FCD_CMD_APP_FIRST_GET_CMD    150
#define FCD_CMD_APP_GET_LNA_GAIN     150 // Retrieve a 1 byte value, see enums for reference
#define FCD_CMD_APP_GET_LNA_ENHANCE  151
#define FCD_CMD_APP_GET_BAND         152
#define FCD_CMD_APP_GET_RF_FILTER    153
#define FCD_CMD_APP_GET_MIXER_GAIN   154
#define FCD_CMD_APP_GET_BIAS_CURRENT 155
#define FCD_CMD_APP_GET_MIXER_FILTER 156
#define FCD_CMD_APP_GET_IF_GAIN1     157
#define FCD_CMD_APP_GET_IF_GAIN_MODE 158
#define FCD_CMD_APP_GET_IF_RC_FILTER 159
#define FCD_CMD_APP_GET_IF_GAIN2     160
#define FCD_CMD_APP_GET_IF_GAIN3     161
#define FCD_CMD_APP_GET_IF_FILTER    162
#define FCD_CMD_APP_GET_IF_GAIN4     163
#define FCD_CMD_APP_GET_IF_GAIN5     164
#define FCD_CMD_APP_GET_IF_GAIN6     165
#define FCD_CMD_APP_GET_BIAS_TEE     166

#define FCD_CMD_APP_RESET            255 // Reset to bootloader


typedef enum 
  {
    TLGE_N5_0DB=0,
    TLGE_N2_5DB=1,
    TLGE_P0_0DB=4,
    TLGE_P2_5DB=5,
    TLGE_P5_0DB=6,
    TLGE_P7_5DB=7,
    TLGE_P10_0DB=8,
    TLGE_P12_5DB=9,
    TLGE_P15_0DB=10,
    TLGE_P17_5DB=11,
    TLGE_P20_0DB=12,
    TLGE_P25_0DB=13,
    TLGE_P30_0DB=14
  } TUNER_LNA_GAIN_ENUM;

typedef enum
  {
    TLEE_OFF=0,
    TLEE_0=1,
    TLEE_1=3,
    TLEE_2=5,
    TLEE_3=7
  } TUNER_LNA_ENHANCE_ENUM;

typedef enum
  {
    TBE_VHF2,
    TBE_VHF3,
    TBE_UHF,
    TBE_LBAND
  } TUNER_BAND_ENUM;

typedef enum
  {
    // Band 0, VHF II
    TRFE_LPF268MHZ=0,
    TRFE_LPF299MHZ=8,
    // Band 1, VHF III
    TRFE_LPF509MHZ=0,
    TRFE_LPF656MHZ=8,
    // Band 2, UHF
    TRFE_BPF360MHZ=0,
    TRFE_BPF380MHZ=1,
    TRFE_BPF405MHZ=2,
    TRFE_BPF425MHZ=3,
    TRFE_BPF450MHZ=4,
    TRFE_BPF475MHZ=5,
    TRFE_BPF505MHZ=6,
    TRFE_BPF540MHZ=7,
    TRFE_BPF575MHZ=8,
    TRFE_BPF615MHZ=9,
    TRFE_BPF670MHZ=10,
    TRFE_BPF720MHZ=11,
    TRFE_BPF760MHZ=12,
    TRFE_BPF840MHZ=13,
    TRFE_BPF890MHZ=14,
    TRFE_BPF970MHZ=15,
    // Band 2, L band
    TRFE_BPF1300MHZ=0,
    TRFE_BPF1320MHZ=1,
    TRFE_BPF1360MHZ=2,
    TRFE_BPF1410MHZ=3,
    TRFE_BPF1445MHZ=4,
    TRFE_BPF1460MHZ=5,
    TRFE_BPF1490MHZ=6,
    TRFE_BPF1530MHZ=7,
    TRFE_BPF1560MHZ=8,
    TRFE_BPF1590MHZ=9,
    TRFE_BPF1640MHZ=10,
    TRFE_BPF1660MHZ=11,
    TRFE_BPF1680MHZ=12,
    TRFE_BPF1700MHZ=13,
    TRFE_BPF1720MHZ=14,
    TRFE_BPF1750MHZ=15
  } TUNER_RF_FILTER_ENUM;

typedef enum
  {
    TMGE_P4_0DB=0,
    TMGE_P12_0DB=1
  } TUNER_MIXER_GAIN_ENUM;

typedef enum
  {
    TBCE_LBAND=0,
    TBCE_1=1,
    TBCE_2=2,
    TBCE_VUBAND=3
  } TUNER_BIAS_CURRENT_ENUM;

typedef enum
  {
    TMFE_27_0MHZ=0,
    TMFE_4_6MHZ=8,
    TMFE_4_2MHZ=9,
    TMFE_3_8MHZ=10,
    TMFE_3_4MHZ=11,
    TMFE_3_0MHZ=12,
    TMFE_2_7MHZ=13,
    TMFE_2_3MHZ=14,
    TMFE_1_9MHZ=15
  } TUNER_MIXER_FILTER_ENUM;

typedef enum
  {
    TIG1E_N3_0DB=0,
    TIG1E_P6_0DB=1
  } TUNER_IF_GAIN1_ENUM;

typedef enum
  {
    TIGME_LINEARITY=0,
    TIGME_SENSITIVITY=1
  } TUNER_IF_GAIN_MODE_ENUM;

typedef enum
  {
    TIRFE_21_4MHZ=0,
    TIRFE_21_0MHZ=1,
    TIRFE_17_6MHZ=2,
    TIRFE_14_7MHZ=3,
    TIRFE_12_4MHZ=4,
    TIRFE_10_6MHZ=5,
    TIRFE_9_0MHZ=6,
    TIRFE_7_7MHZ=7,
    TIRFE_6_4MHZ=8,
    TIRFE_5_3MHZ=9,
    TIRFE_4_4MHZ=10,
    TIRFE_3_4MHZ=11,
    TIRFE_2_6MHZ=12,
    TIRFE_1_8MHZ=13,
    TIRFE_1_2MHZ=14,
    TIRFE_1_0MHZ=15
  } TUNER_IF_RC_FILTER_ENUM;

typedef enum
  {
    TIG2E_P0_0DB=0,
    TIG2E_P3_0DB=1,
    TIG2E_P6_0DB=2,
    TIG2E_P9_0DB=3
  } TUNER_IF_GAIN2_ENUM;

typedef enum
  {
    TIG3E_P0_0DB=0,
    TIG3E_P3_0DB=1,
    TIG3E_P6_0DB=2,
    TIG3E_P9_0DB=3
  } TUNER_IF_GAIN3_ENUM;

typedef enum
  {
    TIG4E_P0_0DB=0,
    TIG4E_P1_0DB=1,
    TIG4E_P2_0DB=2
  } TUNER_IF_GAIN4_ENUM;

typedef enum
  {
    TIFE_5_50MHZ=0,
    TIFE_5_30MHZ=1,
    TIFE_5_00MHZ=2,
    TIFE_4_80MHZ=3,
    TIFE_4_60MHZ=4,
    TIFE_4_40MHZ=5,
    TIFE_4_30MHZ=6,
    TIFE_4_10MHZ=7,
    TIFE_3_90MHZ=8,
    TIFE_3_80MHZ=9,
    TIFE_3_70MHZ=10,
    TIFE_3_60MHZ=11,
    TIFE_3_40MHZ=12,
    TIFE_3_30MHZ=13,
    TIFE_3_20MHZ=14,
    TIFE_3_10MHZ=15,
    TIFE_3_00MHZ=16,
    TIFE_2_95MHZ=17,
    TIFE_2_90MHZ=18,
    TIFE_2_80MHZ=19,
    TIFE_2_75MHZ=20,
    TIFE_2_70MHZ=21,
    TIFE_2_60MHZ=22,
    TIFE_2_55MHZ=23,
    TIFE_2_50MHZ=24,
    TIFE_2_45MHZ=25,
    TIFE_2_40MHZ=26,
    TIFE_2_30MHZ=27,
    TIFE_2_28MHZ=28,
    TIFE_2_24MHZ=29,
    TIFE_2_20MHZ=30,
    TIFE_2_15MHZ=31
  } TUNER_IF_FILTER_ENUM;

typedef enum
  {
    TIG5E_P3_0DB=0,
    TIG5E_P6_0DB=1,
    TIG5E_P9_0DB=2,
    TIG5E_P12_0DB=3,
    TIG5E_P15_0DB=4
  } TUNER_IF_GAIN5_ENUM;

typedef enum
  {
    TIG6E_P3_0DB=0,
    TIG6E_P6_0DB=1,
    TIG6E_P9_0DB=2,
    TIG6E_P12_0DB=3,
    TIG6E_P15_0DB=4
  } TUNER_IF_GAIN6_ENUM;


// FCD PRO PLUS

typedef enum
{
  PP_TLGE_OFF = 0,
  PP_TLGE_ON = 1
} PP_TUNER_LNA_GAIN_ENUM;

typedef enum
{
  PP_TMGE_OFF = 0,
  PP_TMGE_ON = 1
} PP_TUNER_MIXER_GAIN_ENUM;


typedef enum
{
    PP_TRFE_0_4 = 0,
    PP_TRFE_4_8,
    PP_TRFE_8_16,
    PP_TRFE_16_32,
    PP_TRFE_32_75,
    PP_TRFE_75_125,
    PP_TRFE_125_250,
    PP_TRFE_145,
    PP_TRFE_410_875,
    PP_TRFE_435,
    PP_TRFE_875_2000
} PP_TUNER_RF_FILTER_ENUM;

typedef enum
{
    PP_TIFE_200KHZ = 0,
    PP_TIFE_300KHZ,
    PP_TIFE_600KHZ,
    PP_TIFE_1536KHZ,
    PP_TIFE_5MHZ,
    PP_TIFE_6MHZ,
    PP_TIFE_7MHZ,
    PP_TIFE_8MHZ
} PP_TUNER_IF_FILTER;

typedef enum
{
  PP_BTE_OFF = 0,
  PP_BTE_ON  = 1
} PP_BIAS_TEE_ENUM;


#endif // LIBFCD_H
