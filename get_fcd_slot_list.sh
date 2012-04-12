#!/bin/bash
#
# script to generate the list of physical slot numbers corresponding
# to currently inserted funcube dongles
#
# The numbers are in the same order as the current enumeration of funcube
# devices by both alsa and libusb.

ls -1lt /dev/snd/by-path/ \
| grep -v '^total' \
| sort -k11 \
| gawk -vFS=: '{a=$3; printf "%s\n", gensub("^1.", "", "g", a)}' \
> /var/lib/misc/fcd_slot_list
