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

OJS= main.c
FLAGS= -lGL -lSDL2 -lSDL2_mixer -lglut -lm -lX11 -lGLU
LFLAGS= -lm -I../include/ -L../include/GL -L../libs/SDL2 -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -mwindows -lfreeglut -lglu32 -lopengl32 
CC= gcc
WCC = i686-w64-mingw32-gcc
WFLAGS = -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lversion -luuid
OUT=../bin/duum
WOUT=../winbin/duum.exe
BINPATH=../bin/lduum
WINPATH=../winbin/
LOUT=launcher
MV=$(shell cp -r ../res/* ../bin/res/ $<)
WMV=$(shell cp -r ../res/* ../winbin/res/ &<)
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
	BINPATH=${WINPATH}launcher.exe
endif 

ifdef PREFIX
	CC=$(PREFIX)-gcc
endif

ifdef OFAST
	OPT=Ofast
endif

target:
	${CC} -o ${OUT} ${OJS} ./png/lodepng.c -pedantic ${ERR} -${OPT} ${FLAGS} 
	${CC} -o ${BINPATH} ./launcher/main.c -${OPT}
	${MV}
	@echo Build Done! Check ${OUT}
