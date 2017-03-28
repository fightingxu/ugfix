###############################################
#makefile for ugcts by CHENYH 17:04 2011/9/21
#

SRCFILES=FMQStatusFile InFMQ OutFMQ UDLFMQ UGFMQ  ksugbu

INCFLAG = -I../xinc

CCFLAG=-g -DLinux -DMT
CC=g++
LINKFLAG=-Xlinker

LIBPATH=-L../lib
LIBS=-lugbases -lxpack -lksfmq -lstdc++ -lpthread


all: ugfmq
	@echo "ugfmq built successful!"

ugfmq: $(SRCFILES:=.o)
	g++ $(LINKFLAG) $(CCFLAG) $(LIBPATH) -o $@ $(SRCFILES:=.o) $(LIBS)


.cpp.o:
	g++ $(CCFLAG) -c $(INCFLAG) $*.cpp

.c.o:
	gcc $(CCFLAG) -c $(INCFLAG) $*.c


# =====================================================

clean:
	rm -f *.o
	rm -f *.c
