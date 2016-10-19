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

fcdsrv: libfcd.a fcdsrv.o
	g++ $(GPP_OPTS) -I$(LIBUSB_INCLUDE_PATH) -o $@ fcdsrv.o -L. -lfcd -lusb-1.0 -lboost_system

fcdsrv.o: fcdsrv.cpp
	g++ -c $(GPP_OPTIONS) -o $@ $< -I$(LIBUSB_INCLUDE_PATH) -I websocketpp -I rapidjson/include

clean:
	rm -f fcdsrv.o libfcd.a fcd winfcdsrv.o libwinfcd.o


### windows version

libwinfcd.a:	libfcd.h libfcd.c Makefile
	$(WINGCC) $(GCC_OPTIONS) -c  -I$(LIBUSB_INCLUDE_PATH) -o libwinfcd.o libfcd.c  -lusb-1.0
	$(WINAR) rcs libwinfcd.a libwinfcd.o

winfcdsrv.o: fcdsrv.cpp
	$(WINGPP) -c $(GPP_OPTIONS) -DWIN32 -o $@ $< -I$(LIBUSB_INCLUDE_PATH) -I websocketpp -I rapidjson/include

winfcdsrv.exe: libwinfcd.a winfcdsrv.o
	$(WINGPP) $(GPP_OPTS) -static -I$(LIBUSB_INCLUDE_PATH) -o $@ winfcdsrv.o -L. -lwinfcd -Llibusb/MinGW32/static -lusb-1.0 -Lboost_1_54_0/bin.v2/libs/system/build/gcc-mingw-mingw/release/link-static/threading-multi/ -lboost_system -lwsock32 -lmswsock -lwinusb -lws2_32
	$(WINSTRIP) $@
