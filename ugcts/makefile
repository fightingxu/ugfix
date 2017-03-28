###############################################
#makefile for ugcts by CHENYH 17:04 2011/9/21
#

SRCFILES=CJThread DRTPData InThread KSCTS ksugbu GetErrInfo OutThread ugcts2di ugdb2di

DB2PATH=/home/db2inst1/sqllib
APPDIR=$(HOME)

INCFLAG = -I../xinc -I$(DB2PATH)/include

CCFLAG=-g -DLinux
CC=g++
LINKFLAG=-Xlinker

LIBPATH=-L$(DB2PATH)/lib -L../lib
LIBS=-lugbases -lxpack -lbccclt3 -lbccsvr3 -ldb2 -lstdc++


all: connected ugcts
	@echo "ugcts built successful!"
	db2 connect reset

connected:
	db2 connect to ksdbs

ugcts: $(SRCFILES:=.o)
	g++ $(LINKFLAG) $(CCFLAG) $(LIBPATH) -o ../bin3/$@ $(SRCFILES:=.o) $(LIBS)


.SUFFIXES:.sqc .cxx

.cxx.sqc:
	cp $*.cxx $*.sqc

.cpp.o:
	g++ $(CCFLAG) -c $(INCFLAG) $*.cpp
.sqc.c:
	db2 prep $*.sqc bindfile
	db2 bind $*.bnd
	db2 grant execute on package $* to public

.c.o:
	gcc $(CCFLAG) -c $(INCFLAG) $*.c


# =====================================================

clean:
	rm -f *.o
	rm -f *.c
	rm -f *.bnd
