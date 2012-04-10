LIBUSB_INCLUDE_PATH=/usr/include/libusb-1.0
#GCC_LIB_OPTIONS=-fpic

all:	libfcd.a fcd


libfcd.a:	libfcd.h libfcd.c hidapi.h hid-libusb.c hidmac.c hidwin.cpp Makefile
	gcc -c  -I$(LIBUSB_INCLUDE_PATH) -o libfcd.o libfcd.c  -lusb-1.0
	gcc -c  -I$(LIBUSB_INCLUDE_PATH) -o hid-libusb.o hid-libusb.c -lusb-1.0
	ar rcs libfcd.a libfcd.o hid-libusb.o

fcd: libfcd.a fcd.c Makefile
	gcc -o fcd fcd.c -I$(LIBUSB_INCLUDE_PATH) -I. -L. -lfcd -lusb-1.0
