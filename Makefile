LIBUSB_INCLUDE_PATH=/usr/include/libusb-1.0

CXX := gcc

all: libfcd.a fcd
all: CCOPTS := -fpic -O2 -Wall
  
debug: libfcd.a fcd
debug: CCOPTS := -fpic -O -g3 -Wall

libfcd.a:	libfcd.h libfcd.c Makefile
	$(CXX) $(CCOPTS) -c  -I$(LIBUSB_INCLUDE_PATH) -o libfcd.o libfcd.c  -lusb-1.0
	ar rcs libfcd.a libfcd.o

fcd: libfcd.a fcd.c Makefile
	$(CXX) $(CCOPTS) -o fcd fcd.c -I$(LIBUSB_INCLUDE_PATH) -I. -L. -lfcd -lusb-1.0

install: fcd
	strip fcd
	su -c 'cp fcd /usr/bin'

clean:
	rm -f libfcd.o libfcd.a fcd
