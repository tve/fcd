LIBUSB_INCLUDE_PATH=/usr/include/libusb-1.0

CC ?= gcc
STRIP ?= strip
DESTDIR ?= /

all: libfcd.a fcd
all: CCOPTS := -fpic -O2 -Wall
  
debug: libfcd.a fcd
debug: CCOPTS := -fpic -O -g3 -Wall

libfcd.a:	libfcd.h libfcd.c Makefile
	$(CC) $(CCOPTS) -c  -I$(LIBUSB_INCLUDE_PATH) -o libfcd.o libfcd.c  -lusb-1.0
	ar rcs libfcd.a libfcd.o

fcd: libfcd.a fcd.c Makefile
	$(CC) $(CCOPTS) -o fcd fcd.c -I$(LIBUSB_INCLUDE_PATH) -I. -L. -lfcd -lusb-1.0

install: fcd
	$(STRIP) fcd
	install -d $(DESTDIR)/usr/bin
	install -m 755 fcd $(DESTDIR)/usr/bin

clean:
	rm -f libfcd.o libfcd.a fcd
