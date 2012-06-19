LIBUSB_INCLUDE_PATH=/usr/include/libusb-1.0
#GCC_LIB_OPTIONS=-fpic
GCC_OPTIONS=-g -O2
all:	libfcd.a fcd


libfcd.a:	libfcd.h libfcd.c hidapi.h hid-libusb.c hidmac.c hidwin.cpp Makefile
	gcc $(GCC_OPTIONS) -c  -I$(LIBUSB_INCLUDE_PATH) -o libfcd.o libfcd.c  -lusb-1.0
	gcc $(GCC_OPTIONS) -c  -I$(LIBUSB_INCLUDE_PATH) -o hid-libusb.o hid-libusb.c -lusb-1.0
	ar rcs libfcd.a libfcd.o hid-libusb.o

fcd: libfcd.a fcd.c Makefile
	gcc $(GCC_OPTIONS) -o fcd fcd.c -I$(LIBUSB_INCLUDE_PATH) -I. -L. -lfcd -lusb-1.0 -lpthread

install: fcd
	su -c 'cp fcd /usr/bin'
