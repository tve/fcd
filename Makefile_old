LIBUSB_INCLUDE_PATH=/usr/include/libusb-1.0
#GCC_LIB_OPTIONS=-fpic
#GCC_OPTIONS=-Wall -g -O2 -fpic
GCC_OPTIONS=-Wall -g3 -fpic
#GPP_OPTIONS=-Wall -O2  -std=c++0x
GPP_OPTIONS=-Wall -g3  -std=c++0x
WINGPP=i686-w64-mingw32-g++
WINGCC=i686-w64-mingw32-gcc
WINAR=i686-w64-mingw32-ar
WINSTRIP=i686-w64-mingw32-strip

all:	libfcd.a fcd

libfcd.a:	libfcd.h libfcd.c Makefile
	gcc $(GCC_OPTIONS) -c  -I$(LIBUSB_INCLUDE_PATH) -o libfcd.o libfcd.c  -lusb-1.0
	ar rcs libfcd.a libfcd.o

fcd: libfcd.a fcd.c Makefile
	gcc $(GCC_OPTIONS) -o fcd fcd.c -I$(LIBUSB_INCLUDE_PATH) -I. -L. -lfcd -lusb-1.0

install: fcd
	strip fcd
	su -c 'cp fcd /usr/bin'

clean:
	rm -f libfcd.a fcd
