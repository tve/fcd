LIBUSB_INCLUDE_PATH=/usr/include/libusb-1.0
#GCC_LIB_OPTIONS=-fpic
GCC_OPTIONS=-Wall -g -O2 -fpic
all:	libfcd.a fcd

# generate hash functions for lookup of parameter names and value strings
fcd_pro_keywords.c: fcd_pro_keywords.txt
	gperf -t -D $< > $@

fcd_pro_plus_keywords.c: fcd_pro_plus_keywords.txt
	gperf -t -D $< > $@

libfcd.a:	libfcd.h libfcd.c Makefile
	gcc $(GCC_OPTIONS) -c  -I$(LIBUSB_INCLUDE_PATH) -o libfcd.o libfcd.c  -lusb-1.0
	ar rcs libfcd.a libfcd.o

fcd: libfcd.a fcd.c Makefile
	gcc $(GCC_OPTIONS) -o fcd fcd.c -I$(LIBUSB_INCLUDE_PATH) -I. -L. -lfcd -lusb-1.0

install: fcd
	su -c 'cp fcd /usr/bin'
