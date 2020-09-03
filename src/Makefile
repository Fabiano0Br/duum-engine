#################################################################################
#										#
#			   GNU makefile for DuuM				#
#										#
# Compilation instructions for:							#
#										#
# GNU/Linux: make								#
# MS-Windows (32 bit) : make WINDOWS=1						#
# FreeBSD: gmake CC=clang							#
#										#
# Flags:									#
# 										#
# CLANG: compile with clang							#
# DEBUG: compiles debug version and shows Wall and Wextra warnings		#
# WINDOWS: compiles for windows							#
# OFAST: enables Ofast level of optimization ( Not recommended )		#
#										#
#								24/08/2020	#			
#################################################################################

FLAGS=-I. -lGL -lSDL2 -lSDL2_mixer -lglut -lm -lGLU
LFLAGS=-lm -I../include/ -L../include/GL -L../libs/SDL2 -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -mwindows -lfreeglut -lglu32 -lopengl32 
CC=gcc
WCC=i686-w64-mingw32-gcc
WFLAGS=-ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lversion -luuid

BINDIR=../bin
WBINDIR=../winbin
OUT=$(BINDIR)/duum
WOUT=$(WBINDIR)/duum.exe
BINPATH=$(BINDIR)/lduum
WINPATH=$(WBINDIR)/
LOUT=launcher
OBJ_SOIL= \
  png/image_helper.o \
  png/stb_image_aug.o  \
  png/image_DXT.o \
  png/SOIL.o
OBJ_DUUM=main.o
OBJ_ALL=$(OBJ_DUUM) $(OBJ_SOIL) ./png/lodepng.o

MV=$(shell cp -r ../res/* ../bin/res/)
WMV=$(shell cp -r ../res/* ../winbin/res/)
OPT=O3

ifdef CLANG
	CC=clang
endif

ifdef DEBUG
	ERR=-Wall -Wextra 
endif

ifdef WINDOWS
	FLAGS=${LFLAGS} ${WFLAGS}
	MV=${WMV}
	OUT=${WOUT}
	BINDIR=${WBINDIR}
	BINPATH=${WINPATH}launcher.exe
endif 

ifdef PREFIX
	CC=$(PREFIX)-gcc
endif

ifdef OFAST
	OPT=Ofast
endif

LD=$(CC)

default: ${OUT} ${BINPATH}
	${MV}
	@echo Build Done! Check ${OUT}

%.o: %.c
	${CC} -o $@ -c $< -pedantic ${ERR} -${OPT} ${FLAGS}

${OUT}: ${OBJ_ALL}
	${LD} -o $@ $? -pedantic ${ERR} -${OPT} ${FLAGS}

${BINPATH}: ./launcher/main.o
	${LD} -o $@ $? -${OPT}

clean:
	rm -f ${OBJ_ALL} ./launcher/main.o
