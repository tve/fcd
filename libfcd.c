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

#include <string.h>
#include <stdlib.h>
#include "libfcd.h"
#include <stdio.h>
#include <unistd.h>

const unsigned short _usVID[] = {0x04D8, 0x04D8};  /*!< USB vendor ID enumerated by FCD_MODEL_ENUM */
const unsigned short _usPID[] = {0xFB56, 0xFB31};  /*!< USB product ID enumerated by FCD_MODEL_ENUM */

char *FCD_MODEL_NAMES[] = {"FCD Pro", "FCD Pro Plus"};

#define FALSE 0
#define TRUE 1
typedef int BOOL;

static libusb_context * ctx = 0;

extern FCD_RETCODE_ENUM fcdInitLibrary() {
  return libusb_init (&ctx);
}

extern FCD_RETCODE_ENUM fcdShutDownLibrary() {
  if (ctx)
    libusb_exit(ctx);
  return FCD_RETCODE_OKAY;
}

/** \brief Open FCD device.
  * \param fcd Pointer to a pre-allocated FCD device descriptor, whose fields will be filled by this function.
  * \param enumNum enumeration number of device to open; 0 means first FCD, 1 means 2nd FCD, etc.
  * \param busNum bus number of device to open
  * \param devNum number of device (on bus busNum) to open
  * \return The parameter fcd, or NULL if the matching FCD was not found.
  *
  * This function looks for FCD devices connected to the computer and
  * opens the first one found that matches the target busNum and devNum,
  * or the enumNum'th one if busNum and devNum are 0.  Using busNum and devNum
  * provides stability of nomenclature across plugging/unplugging of other FCDs.
  */
extern FCD_RETCODE_ENUM fcdOpen(fcdDesc *fcd, uint16_t enumNum, uint8_t busNum, uint8_t devNum)
{
  libusb_device **list;
  libusb_device *found = NULL;

  uint16_t currEnumNum = -1;

  if (!ctx && fcdInitLibrary())
    return FCD_RETCODE_ERROR;

  if (!fcd)
    return FCD_RETCODE_ERROR;

  fcd->phd = NULL; // assume no matching FCD found

  ssize_t i = 0;

  ssize_t cnt = libusb_get_device_list(ctx, &list);
  if (cnt < 0)
    return FCD_RETCODE_ABSENT;

  FCD_RETCODE_ENUM rv;

  FCD_MODEL_ENUM model;
    
    for (i = 0; i < cnt; i++) {
      libusb_device *device = list[i];
      struct libusb_device_descriptor dsc;
      if (libusb_get_device_descriptor(device, &dsc)) {
	rv = FCD_RETCODE_ERROR;
	break;
      }

      // check whether this device is an FCD
      int is_fcd = FALSE;
      for (model = FCD_MODEL_FIRST_MODEL; model <= FCD_MODEL_LAST_MODEL; ++model) {
	if (dsc.idVendor == _usVID[model]  && dsc.idProduct == _usPID[model]) {
	  currEnumNum++;
	  is_fcd = TRUE;
	  break;
	}
      }
      if (is_fcd) {
	if (busNum > 0) {
	  if (libusb_get_bus_number(device) == busNum && libusb_get_device_address(device) == devNum) {
	    found = device;
	    break;
	  }
	} else {
	  if (enumNum == currEnumNum) {
	    found = device;
	    break;
	  }
	}
      }
    }
	
    if (found) {
      if (libusb_open(found, &fcd->phd)) {
	rv = FCD_RETCODE_ERROR;
      } else {
	int kernel_owns = libusb_kernel_driver_active(fcd->phd, FCD_SETTINGS_INTERFACE);
	if (kernel_owns < 0
	    || (kernel_owns == 1 && libusb_detach_kernel_driver(fcd->phd, FCD_SETTINGS_INTERFACE) != 0) 
	    || libusb_claim_interface(fcd->phd, FCD_SETTINGS_INTERFACE) != 0) {
	  libusb_close(fcd->phd);
	  rv = FCD_RETCODE_ERROR;
	} else {
	  fcd->busNum = libusb_get_bus_number(found);
	  fcd->devNum = libusb_get_device_address(found);
	  fcd->enumNum = currEnumNum;
	  fcd->model = model;
	  fcd->pszModelName = strdup(FCD_MODEL_NAMES[model]);
	  rv = FCD_RETCODE_OKAY;
	}
      }
    } else {
      rv = FCD_RETCODE_ERROR;
    }
    libusb_free_device_list(list, 1);
    return rv;
}



/** \brief Close FCD HID device.
  * \param fcd Pointer to an FCD device descriptor 
  */
extern FCD_RETCODE_ENUM fcdClose(fcdDesc *fcd)
{
    if (! (fcd && fcd->phd))
	return FCD_RETCODE_ABSENT;

    if (fcd->phd) {
      libusb_release_interface(fcd->phd, FCD_SETTINGS_INTERFACE);
      libusb_close(fcd->phd);
      fcd->phd = NULL;
    }
    if (fcd->pszModelName) {
	free(fcd->pszModelName);
	fcd->pszModelName = NULL;
    }
    return FCD_RETCODE_OKAY;
}

static FCD_RETCODE_ENUM fcdSendCommand(fcdDesc *fcd, uint8_t cmd, uint8_t *data, uint16_t len, uint8_t *reply, uint16_t replyLen) {
  uint8_t buf[64];

  if (!(fcd && fcd->phd))
    return FCD_RETCODE_ABSENT;

  buf[0] = cmd;
  if (data)
    memcpy(& buf[1], data, len <= 64 ? len : 64);
  int transferred = 0;
  int err;
  err = libusb_interrupt_transfer (fcd->phd,
				   FCD_SEND_COMMAND_ENDPOINT,
				   & buf[0],
				   64,
				   & transferred,
				   2500); // timeout in milliseconds
  if (err) 
    return FCD_RETCODE_ERROR;
  err = libusb_interrupt_transfer (fcd->phd,
				   FCD_RECEIVE_REPLY_ENDPOINT,
				   & buf[0],
				   64,
				   & transferred,
				   2500);

  if (err || buf[0] != cmd || buf[1] != 1)
    return FCD_RETCODE_ERROR;

  if (reply)
    memcpy(reply, &buf[2], replyLen <= 62 ? replyLen : 62);

  return FCD_RETCODE_OKAY;
}
    

/** \brief Get FCD mode.
  * \param fcd Pointer to an FCD device descriptor 
  * \param pMode Pointer to a pre-allocated FCD_MODE_ENUM field. in which the current mode is returned.
  * \return Return code.
  * \sa FCD_RETCODE_ENUM
  */
extern FCD_RETCODE_ENUM fcdGetMode(fcdDesc *fcd, FCD_MODE_ENUM *pMode)
{
    unsigned char buf[64];

    if (!pMode)
	return FCD_RETCODE_ERROR;

    FCD_RETCODE_ENUM err = fcdSendCommand(fcd, FCD_CMD_BL_QUERY, 0, 0, & buf[0], 64);

    if (err)
      return err;

    if (strncmp((char *)buf, "FCDBL", 5) == 0) {
      *pMode = FCD_MODE_BL;
    }
    /* In application mode we have "FCDAPP_18.06" where the number is the FW version */
    else if (strncmp((char *)buf, "FCDAPP", 6) == 0) {
      *pMode = FCD_MODE_APP;
    }
    /* either no FCD or firmware less than 18f */
    else {
      return FCD_RETCODE_ERROR;
    }
    return FCD_RETCODE_OKAY;
}


/** \brief Get FCD firmware version as string.
  * \param fcd Pointer to an FCD device descriptor 
  * \param str The returned vesion number as a 0 terminated string (must be pre-allocated)
  * \return The current FCD mode.
  * \sa FCD_RETCODE_ENUM
  */
extern FCD_RETCODE_ENUM fcdGetFwVerStr(fcdDesc *fcd, char *str)
{
    unsigned char buf[64];

    if (!str)
	return FCD_RETCODE_ERROR;

    FCD_RETCODE_ENUM err = fcdSendCommand(fcd, FCD_CMD_BL_QUERY, 0, 0, & buf[0], 64);

    if (err)
      return err;
    if (strncmp((char *)buf, "FCDAPP", 6) == 0) {
      strncpy(str, (char*) &buf[7], 5);
      str[5] = 0;
      return FCD_RETCODE_OKAY;
    }
    return FCD_RETCODE_ERROR;
}

/** \brief Reset FCD to application mode.
  * \param fcd Pointer to an FCD device descriptor 
  * \return FCD_MODE_NONE
  *
  * This function is used to switch the FCD from bootloader mode
  * into application mode.
  */
extern FCD_RETCODE_ENUM fcdBlReset(fcdDesc *fcd)
{
  // Send an BL reset command
   return fcdSendCommand(fcd, FCD_CMD_BL_RESET, 0, 0, 0, 0);
}

/** \brief Reset FCD to bootloader mode.
  * \param fcd Pointer to an FCD device descriptor 
  * \return FCD_MODE_NONE
  *
  * This function is used to switch the FCD into bootloader mode in which
  * various firmware operations can be performed.
  */
extern FCD_RETCODE_ENUM fcdAppReset(fcdDesc *fcd)
{
   return fcdSendCommand(fcd, FCD_CMD_APP_RESET, 0, 0, 0, 0);
}


/** \brief Set FCD frequency with kHz resolution.
  * \param fcd Pointer to an FCD device descriptor 
  * \param nFreq The new frequency in kHz.
  * \return the return code.
  *
  * This function sets the frequency of the FCD with 1 kHz resolution. The parameter
  * nFreq must already contain any necessary frequency correction.
  *
  * \sa fcdAppSetFreq
  */
extern FCD_RETCODE_ENUM fcdAppSetFreqkHz(fcdDesc *fcd, int nFreq)
{
  return fcdSendCommand(fcd, FCD_CMD_APP_SET_FREQ_KHZ, (uint8_t *) &nFreq, 3, 0, 0);
}

/** \brief Set FCD frequency with Hz resolution.
  * \param fcd Pointer to an FCD device descriptor 
  * \param nFreq The new frequency in Hz.
  * \return the return code.
  *
  * This function sets the frequency of the FCD with 1 Hz resolution. The parameter
  * nFreq must already contain any necessary frequency correction.
  *
  * \sa fcdAppSetFreqkHz
  */
extern FCD_RETCODE_ENUM fcdAppSetFreq(fcdDesc *fcd, uint32_t nFreq, uint32_t *actualFreq)
{
  return fcdSendCommand(fcd, FCD_CMD_APP_SET_FREQ_HZ, (uint8_t *) &nFreq, 4, (uint8_t *) actualFreq, 4);
}

/** \brief Get FCD frequency with Hz resolution.
  * \param fcd Pointer to an FCD device descriptor 
  * \param nFreq Pointer to a preallocated loation for storing the current frequency in Hz.
  * \return the return code.
  *
  * This function obtains the current frequency of the FCD with 1 Hz resolution.  The frequency 
  * returned includes any necessary frequency correction, and so is not the "true" frequency. 
  *
  * \sa fcdAppSetFreqHz
  */
extern FCD_RETCODE_ENUM fcdAppGetFreq(fcdDesc *fcd, uint32_t *nFreq)
{  
    if (!nFreq) {
        return FCD_RETCODE_ERROR;
    }

    return fcdSendCommand(fcd, FCD_CMD_APP_GET_FREQ_HZ, 0, 0, (uint8_t *) nFreq, 4);

}


/** \brief Write FCD parameter (e.g. gain or filter)
  * \param fcd Pointer to an FCD device descriptor 
  * \param u8Cmd The command byte / parameter ID, see FCD_CMD_APP_SET_*
  * \param pu8Data The parameter value to be written
  * \param u8len Length of pu8Data in bytes
  * \return One of FCD_MODE_NONE, FCD_MODE_APP or FCD_MODE_BL (see description)
  *
  * This function can be used to set the value of a parameter in the FCD for which there is no
  * high level API call. It gives access to the low level API of the FCD and the caller is expected
  * to be aware of the various FCD commands, since they are required to be supplied as parameter
  * to this function.
  *
  * The return value can be used to determine the success or failure of the command execution:
  * - FCD_MODE_APP : Reply from FCD was as expected (nominal case).
  * - FCD_MODE_BL : Reply from FCD was not as expected.
  * - FCD_MODE_NONE : No FCD was found
  */
extern FCD_RETCODE_ENUM fcdAppSetParam(fcdDesc *fcd, uint8_t u8Cmd, uint8_t *pu8Data, uint8_t u8len)
{
  return fcdSendCommand(fcd, u8Cmd, pu8Data, u8len, 0, 0);
}


/** \brief Read FCD parameter (e.g. gain or filter)
  * \param fcd Pointer to an FCD device descriptor 
  * \param u8Cmd The command byte / parameter ID, see FCD_CMD_APP_GET_*
  * \param pu8Data TPointer to buffer where the parameter value(s) will be written
  * \param u8len Length of pu8Data in bytes
  * \return One of FCD_MODE_NONE, FCD_MODE_APP or FCD_MODE_BL (see description)
  *
  * This function can be used to read the value of a parameter in the FCD for which there is no
  * high level API call. It gives access to the low level API of the FCD and the caller is expected
  * to be aware of the various FCD commands, since they are required to be supplied as parameter
  * to this function.
  *
  * The return value can be used to determine the success or failure of the command execution:
  * - FCD_MODE_APP : Reply from FCD was as expected (nominal case).
  * - FCD_MODE_BL : Reply from FCD was not as expected.
  * - FCD_MODE_NONE : No FCD was found
  */
extern FCD_RETCODE_ENUM fcdAppGetParam(fcdDesc *fcd, uint8_t u8Cmd, uint8_t *pu8Data, uint8_t u8len)
{
  return fcdSendCommand(fcd, u8Cmd, 0, 0, pu8Data, u8len);
}

/** \brief Set default gain and filter parameters
  * \param fcd Pointer to an FCD device descriptor 
  */

typedef struct {

  uint8_t parm;
  uint8_t value;

} param_value;

static param_value param_defaults[] = {

  {FCD_CMD_APP_SET_LNA_GAIN    , TLGE_P20_0DB}, 
  {FCD_CMD_APP_SET_LNA_ENHANCE , TLEE_OFF},
  {FCD_CMD_APP_SET_BAND        , TBE_VHF2},
  {FCD_CMD_APP_SET_RF_FILTER   , TRFE_LPF268MHZ},
  {FCD_CMD_APP_SET_MIXER_GAIN  , TMGE_P12_0DB},
  {FCD_CMD_APP_SET_BIAS_CURRENT, TBCE_VUBAND},
  {FCD_CMD_APP_SET_MIXER_FILTER, TMFE_1_9MHZ},
  {FCD_CMD_APP_SET_IF_GAIN1    , TIG1E_P6_0DB},
  {FCD_CMD_APP_SET_IF_GAIN_MODE, TIGME_LINEARITY},
  {FCD_CMD_APP_SET_IF_RC_FILTER, TIRFE_1_0MHZ},
  {FCD_CMD_APP_SET_IF_GAIN2    , TIG2E_P0_0DB},
  {FCD_CMD_APP_SET_IF_GAIN3    , TIG3E_P0_0DB},
  {FCD_CMD_APP_SET_IF_FILTER   , TIFE_2_15MHZ},
  {FCD_CMD_APP_SET_IF_GAIN4    , TIG4E_P0_0DB},
  {FCD_CMD_APP_SET_IF_GAIN5    , TIG5E_P3_0DB},
  {FCD_CMD_APP_SET_IF_GAIN6    , TIG6E_P3_0DB},
   {0                           , 0}

} ;

extern FCD_RETCODE_ENUM fcdAppSetParamDefaults(fcdDesc *fcd)
{
  param_value *defs = & param_defaults[0];
  while (defs->parm != 0) {
    if (FCD_RETCODE_OKAY != fcdAppSetParam(fcd, defs->parm, &defs->value, 1))
      return FCD_RETCODE_ERROR;
    ++defs;
  }
  return FCD_RETCODE_OKAY;
}
