/***************************************************************************
 *  This file is part of libfcd
 * 
 *  Copyright (C) 2010  Howard Long, G6LVB
 *  Copyright (C) 2011  Alexandru Csete, OZ9AEC
 *                      Mario Lorenz, DL5MLO
 *  Copyright (C) 2012-2015  John Brzustowski
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

/* 

   simple fcd control

*/

#include "libfcd.h"

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

typedef enum {
  OPT_NONE,
  OPT_SERNUM	   = 'n',
  OPT_APPMODE      = 'a',
  OPT_BLMODE       = 'b',
  OPT_FIRMWARE     = 'f',
  OPT_USB_PATH     = 'p',
  OPT_ENUMNUM	   = 'e',
  OPT_LIST	   = 'l',
  OPT_SET_DEFAULTS = 'd',
  OPT_GET_FREQ	   = 'g',
  OPT_SET_FREQ	   = 's',
  OPT_SET_FREQ_MHZ = 'm',
  OPT_SET_FREQ_KHZ = 'k',
  OPT_SET_PARAMS   = 'w',
  OPT_RESET_DEV    = 'R',
  OPT_GET_PARAMS   = 'r',
  OPT_GET_VERSION  = 'v',
  OPT_QUIET        = 'q'
} cmds_t;

int
main(int argc, char **argv)
{
  int c;
  cmds_t command = OPT_NONE;
  int enumNum = 0;
  int quiet = 0;
  uint32_t freq;
  fcdDesc fcd;
  int devOpen = 0;
  uint8_t busNum = 0;
  uint8_t devNum = 0;
  char *firmware_path = 0;

  static struct option long_options[] = {
    {"appmode",    0, 0, OPT_APPMODE},
    {"blmode",     0, 0, OPT_BLMODE},
    {"firmware",   1, 0, OPT_FIRMWARE},
    {"serialnum",  1, 0, OPT_SERNUM},
    {"path",       1, 0, OPT_USB_PATH},
    {"enumnum",    1, 0, OPT_ENUMNUM},
    {"list",       0, 0, OPT_LIST},
    {"defaults",   0, 0, OPT_SET_DEFAULTS},
    {"getfreq",    0, 0, OPT_GET_FREQ},
    {"setfreq",    1, 0, OPT_SET_FREQ},
    {"setfreqkHz", 1, 0, OPT_SET_FREQ_KHZ},
    {"setfreqMHz", 1, 0, OPT_SET_FREQ_MHZ},
    {"setparams",  0, 0, OPT_SET_PARAMS},
    {"getparams",  0, 0, OPT_GET_PARAMS},
    {"reset",      0, 0, OPT_RESET_DEV},
    {"version",    0, 0, OPT_GET_VERSION},
    {"quiet",      0, 0, OPT_QUIET},
    {0, 0, 0, 0}
  };

  int have_opt = 0;

  for (;;) {

    c = getopt_long(argc, argv, "abe:f:p:n:ldgs:k:m:wRrqv",
		    long_options, NULL);
    if (c == -1 && have_opt)
      break;

    have_opt = 1;
    switch (c) {
    case OPT_APPMODE:
    case OPT_BLMODE:
    case OPT_LIST:
    case OPT_SET_DEFAULTS:
    case OPT_GET_FREQ:
    case OPT_RESET_DEV:
    case OPT_SET_PARAMS:
    case OPT_GET_PARAMS:
    case OPT_GET_VERSION:
      command = c;
      break;

    case OPT_FIRMWARE:
      command = OPT_FIRMWARE;
      firmware_path = optarg;
      break;

    case OPT_USB_PATH:
      if (2 != sscanf(optarg, "%hhd:%hhd", &busNum, &devNum)) {
	puts("Error: path must be busNum:devNum\n");
	exit(1);
      }
      break;

    case OPT_ENUMNUM:
      enumNum = atoi(optarg);
      break;

    case OPT_SET_FREQ:
      freq = atoi(optarg);
      command = OPT_SET_FREQ;
      break;

    case OPT_SET_FREQ_KHZ:
      freq = atoi(optarg);
      command = OPT_SET_FREQ_KHZ;
      break;

    case OPT_SET_FREQ_MHZ:
      {
        float freqMhz = atof(optarg);
        freq = (uint32_t) (freqMhz * 1.0e6);
        command = OPT_SET_FREQ;
      };
      break;

    case OPT_QUIET:
      quiet = 1;
      continue;
      break;

    default:
      printf("\nUsage: \n\n"
	     "fcd -l   - list available funcube devices\n"
	     "fcd -R [DEVSPEC]  - reset the funcube device\n"
	     "fcd -v [DEVSPEC]  - get the funcube firmware version\n"
	     "fcd [DEVSPEC] -f FIRMWAREFILE - upload new firmware to the funcubedongle\n"
	     "fcd -b [DEVSPEC]  - set the funcube into bootloader mode\n"
	     "fcd -a [DEVSPEC]  - set the funcube into application mode\n"
	     "fcd [-q] [DEVSPEC] -d - set default parameters\n"
	     "fcd [DEVSPEC] -g - get and print current frequency\n"
	     "fcd [-q] [DEVSPEC] -s freq_Hz - set frequency in Hz\n"
	     "fcd [-q] [DEVSPEC] -k freq_kHz - set frequency in kHz\n"
	     "fcd [DEVSPEC] -r [P1 P2 ... Pk] read and print values of parameters P1 ... Pk, or all if none specified\n"
	     "fcd [-q] [DEVSPEC] -w P1 V1 [P2 V2 ... Pk Vk] set values of parameter P1 to V1, P2 to V2, ... Pk to Vk\n"
	     "\n  e.g. fcd -p 1:22 -k 166380 -g -w 0xf 3\n\n"
	     "where [DEVSPEC] chooses a funcube like so:\n\n"
	     "   <blank>: use the first funcube found\n"
	     "   -e n: use the nth funcube found, with n=0 being the first\n"
	     "   -p <path>: use the BUS:DEVICE usb path as shown by fcd -l; e.g. fcd -p 1:22\n"
	     "Option '-q' prevents fcd from printing output.\n"
	     "Parameters P1..Pk and their values V1..Vk  are specified as integers in decimal or hex'\n"
	     "Parameters are numbered from 0 for LNA_GAIN to 15 for IF_GAIN6 - see libfcd.h.\n"
	     "Parameter values are as they appear in the ENUMs in libfcd.h\n"
	     "Values returned by the '-r' option are printed one per line as 0xX 0xY,\n"
	     "where:\n"
	     "   X is the parameter number in hex\n"
	     "   Y is the parameter value in hex\n"
	     );
      exit(1);
    }

    switch(command) {
    case OPT_LIST:
      puts("These FCDs found:");
      for (enumNum=0;/**/ ; ++enumNum) {
	if (FCD_RETCODE_OKAY != fcdOpen(&fcd, enumNum, busNum, devNum, 0)) {
	  break;
	}
	printf("Model: %12s; enum: %2d; path: %d:%d\n", fcd.pszModelName, enumNum, fcd.busNum, fcd.devNum);
	fcdClose(&fcd);
      }	    
      exit(0);
      break;
    case OPT_RESET_DEV:
      if (FCD_RETCODE_OKAY != fcdResetDev(0, enumNum, busNum, devNum)) {
	if (!quiet) puts("Error: unable to set reset specified FCD.");
	exit(1);
      }
      if (!quiet) puts("Device has been reset.");
      break;
      
    default:
      break;
    }
    if (!devOpen && FCD_RETCODE_OKAY != fcdOpen(&fcd, enumNum, busNum, devNum, 0)) {
      if (!quiet) puts("Error: unable to open specified FCD.");
      exit(1);
    }
    devOpen = 1;
    int actualFreq = 0;

    switch(command) {
    case OPT_APPMODE:
      if (FCD_RETCODE_OKAY != fcdBlReset(&fcd)) {
	puts("Error: unable to switch specified FCD to application mode.");
	fcdClose(&fcd);
	exit(1);
      }
      puts("FCD switched to application mode\n");
      break;

    case OPT_BLMODE:
      if (FCD_RETCODE_OKAY != fcdAppReset(&fcd)) {
	puts("Error: unable to switch specified FCD to bootloader mode.");
	fcdClose(&fcd);
	exit(1);
      }
      puts("FCD switched to bootloader mode\n");
      break;
      
    case OPT_GET_VERSION:
      {
        unsigned char fwversion[128];
        if (FCD_RETCODE_OKAY != fcdGetFwVerStrExt(&fcd, fwversion, 128)) {
          puts("Error: unable to get firmware version for specified FCD.");
          fcdClose(&fcd);
          exit(1);
        }
        printf("%s\n", fwversion);
      }
      break;
    case OPT_GET_FREQ:
      if (FCD_RETCODE_OKAY != fcdAppGetFreq(&fcd, &freq)) {
	puts("Error: unable to get frequency for specified FCD.");
	fcdClose(&fcd);
	exit(1);
      }
      printf("%d\n", freq);
      break;
    case OPT_SET_FREQ:
      if (FCD_RETCODE_OKAY != fcdAppSetFreq(&fcd, freq, (uint32_t *)&actualFreq)) {
	if (!quiet) puts("Error: unable to set frequency for specified FCD.");
	fcdClose(&fcd);
	exit(1);
      } else if (!quiet) {
	printf("Frequency set to %d Hz.\n", actualFreq);
      }
      break;
    case OPT_SET_FREQ_KHZ:
      if (FCD_RETCODE_OKAY != fcdAppSetFreqkHz(&fcd, freq)) {
	if (!quiet) puts("Error: unable to set frequency in kHz for specified FCD.");
	fcdClose(&fcd);
	exit(1);
      }
      break;
    case OPT_SET_DEFAULTS:
      if (FCD_RETCODE_OKAY != fcdAppSetParamDefaults(&fcd)) {
	if (!quiet) puts("Error: unable to set default filter and gain parameters for specified FCD.");
	fcdClose(&fcd);
	exit(1);
      }
      if (!quiet) puts("Default gain and filtering parameters set.");
      break;
    case OPT_SET_PARAMS:
      while (optind < argc) {
	uint8_t parno = (uint8_t) strtol(argv[optind++], 0, 0);
	if (optind >= argc) {
	  if (!quiet) printf("Error: missing value for parameter 0x%x\n", parno);
	  exit(1);
	}
	uint8_t parval = (uint8_t) strtol(argv[optind++], 0, 0);
	if (FCD_RETCODE_OKAY != fcdAppSetParam(&fcd, FCD_CMD_APP_FIRST_SET_CMD + parno, &parval, sizeof(parval))) {
	  if (!quiet) printf("Error: unable to set parameter 0x%x to value 0x%x\n", parno, parval);
	}
      }
      fcdClose(&fcd);
      exit(EXIT_SUCCESS);
      break;

    case OPT_GET_PARAMS:
      {
	int get_all = (optind == argc);
	int n = get_all ? FCD_CMD_APP_NUM_PARAMS : (argc - optind);
	int i;
	for (i = 0; i < n; ++i) {
	  uint8_t parno = get_all ? i : (uint8_t) strtol(argv[optind++], 0, 0);
	  uint8_t parval;
	  if (FCD_RETCODE_OKAY == fcdAppGetParam(&fcd, FCD_CMD_APP_FIRST_GET_CMD + parno, &parval, sizeof(parval))) {
	    printf("0x%x 0x%x\n", parno, parval);
	  } else {
	    // silently ignore invalid parameter selection
	  }
	}
	fcdClose(&fcd);
	exit(EXIT_SUCCESS);
      }
      break;

    case OPT_FIRMWARE:
      {
        struct stat finfo;
        if (stat(firmware_path, &finfo)) {
          printf("Error: unable to locate firmware file '%s'\n", firmware_path);
          exit(2);
        }
        unsigned char *fwbuf = (unsigned char *) calloc(1, finfo.st_size);
        if (!fwbuf) {
          printf("Error: unable to allocate %ld bytes for loading firmware '%s'.\n", finfo.st_size, firmware_path);
          exit(3);
        }
        FILE *f = fopen(firmware_path, "rb");
        if ((!f) || 1 != fread(fwbuf, finfo.st_size, 1, f)) {
          printf("Error: unable to read firmware from file '%s'.\n", firmware_path);
          if (f)
            fclose(f);
          exit(3);
        }
        fclose(f);

        if (FCD_RETCODE_OKAY != fcdAppReset(&fcd)) {
          puts("Error: unable to switch specified FCD to bootloader mode.");
          fcdClose(&fcd);
          exit(1);
        }

        sleep(3);  // sleep 3; seems to take this long for device to get re-enumerated.
        
        if (FCD_RETCODE_OKAY != fcdOpen(&fcd, -1, 0, 0, 0x01)) {
          puts("Error: unable to re-open FCD that was switched to bootloader mode.");
          fcdClose(&fcd);
          exit(1);
        }

        uint32_t start, end;
        if (FCD_RETCODE_OKAY != fcdBlGetByteAddrRange(&fcd, &start, &end)) {
          puts("Error: unable to get byte address range from FCD.");
          fcdClose(&fcd);
          exit(1);
        }
        if (FCD_RETCODE_OKAY != fcdBlErase(&fcd)) {
          puts("Error: unable to erase firmware on FCD.");
          fcdClose(&fcd);
          exit(1);
        }
        if (FCD_RETCODE_OKAY != fcdBlWriteFirmware(&fcd, fwbuf, finfo.st_size, start, end)) {
          puts("Error: unable to write firmware to FCD.");
          fcdClose(&fcd);
          exit(1);
        }
        if (FCD_RETCODE_OKAY != fcdBlVerifyFirmware(&fcd, fwbuf, finfo.st_size, start, end)) {
          puts("Error: unable to verify firmware on FCD.");
          fcdClose(&fcd);
          exit(1);
        }
        if (FCD_RETCODE_OKAY != fcdBlReset(&fcd)) {
          puts("Error: unable to switch reflashed FCD back to application mode.");
          fcdClose(&fcd);
          exit(1);
        }
        if (FCD_RETCODE_OKAY != fcdResetDev(&fcd, 0, 0, 0)) {
          puts("Error: unable to reset reflashed FCD back.");
          fcdClose(&fcd);
          exit(1);
        }
      }
      break;

    default:
      break;
    }
  }
  fcdClose(&fcd);
  exit(EXIT_SUCCESS);
}

