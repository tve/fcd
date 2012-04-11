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

/* 

   simple fcd control

*/

#include "libfcd.h"

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

typedef enum {OPT_NONE, OPT_SERNUM='n', OPT_ENUMNUM='e', OPT_LIST='l', OPT_GET_FREQ='g', OPT_SET_FREQ='s', OPT_SET_FREQ_KHZ='k'} cmds_t;

int
main(int argc, char **argv)
{
    int c;
    cmds_t command = OPT_NONE;
    int serialNum = 0;
    int enumNum = 0;
    uint32_t freq;
    fcdDesc fcd;

    static struct option long_options[] = {
	{"serialnum",  1, 0, OPT_SERNUM},
	{"enumnum",    1, 0, OPT_ENUMNUM},
	{"list",       0, 0, OPT_LIST},
	{"getfreq",    0, 0, OPT_GET_FREQ},
	{"setfreq",    1, 0, OPT_SET_FREQ},
	{"setfreqkHz", 1, 0, OPT_SET_FREQ_KHZ},
	{0, 0, 0, 0}
    };

    for (;;) {

	c = getopt_long(argc, argv, "e:n:lgs:k:",
			long_options, NULL);
	if (c == -1)
	    break;

	switch (c) {
	case OPT_LIST:
	    command = OPT_LIST;
	    break;

	case OPT_SERNUM:
	    serialNum = atoi(optarg);
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

	case OPT_GET_FREQ:
	    command = OPT_GET_FREQ;
	    break;

	default:
	    printf("usage: fcd [-l] [-e enumno] [-n sernum] [-g] [-s freq_Hz] [-k freq_kHz]\n");
	    exit(1);
	}
    }

    switch(command) {
    case OPT_LIST:
	puts("These FCDs found:");
	for (enumNum=0, serialNum=0;; ++enumNum) {
	    if (FCD_RETCODE_OKAY != fcdOpen(&fcd, serialNum, enumNum)) {
		break;
	    }
	    printf("enum: %2d; serial: %6d; path: %s\n", fcd.enumNum, fcd.serialNum, fcd.pszPath);
	    fcdClose(&fcd);
	}	    
	exit(0);
	break;
    default:
	break;
    }
    if (FCD_RETCODE_OKAY != fcdOpen(&fcd, serialNum, enumNum)) {
	puts("Error: unable to open specified FCD.");
	exit(1);
    }
    switch(command) {
    case OPT_GET_FREQ:
	if (FCD_RETCODE_OKAY != fcdAppGetFreq(&fcd, &freq)) {
	    puts("Error: unable to get frequency for specified FCD.");
	    exit(1);
	}
	printf("%d Hz\n", freq);
	break;
    case OPT_SET_FREQ:
	if (FCD_RETCODE_OKAY != fcdAppSetFreq(&fcd, freq)) {
	    puts("Error: unable to set frequency for specified FCD.");
	    exit(1);
	}
	printf("%d Hz\n", freq);
	break;
    case OPT_SET_FREQ_KHZ:
	if (FCD_RETCODE_OKAY != fcdAppSetFreqkHz(&fcd, freq)) {
	    puts("Error: unable to set frequency in kHz for specified FCD.");
	    exit(1);
	}
	printf("%d kHz\n", freq);
	break;
    default:
	break;
    }
    exit(EXIT_SUCCESS);
}
