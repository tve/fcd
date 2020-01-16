LIBUSB_INCLUDE_PATH=/usr/include/libusb-1.0
#GCC_LIB_OPTIONS=-fpic

GCC_DBG_OPTIONS=-fpic -O -g3 -Wall
GCC_PROD_OPTIONS=-fpic -O2 -Wall
GCC_OPTIONS=$(GCC_PROD_OPTIONS)

all:	libfcd.a fcd

libfcd.a:	libfcd.h libfcd.c Makefile
	gcc $(GCC_OPTIONS) -c  -I$(LIBUSB_INCLUDE_PATH) -o libfcd.o libfcd.c  -lusb-1.0
	ar rcs libfcd.a libfcd.o

fcd: libfcd.a fcd.c Makefile
	gcc $(GCC_OPTIONS) -o fcd fcd.c -I$(LIBUSB_INCLUDE_PATH) -I. -L. -lfcd -lusb-1.0

install: fcd
	su -c 'cp fcd /usr/bin'

clean:
	rm -f libfcd.o libfcd.a fcd
