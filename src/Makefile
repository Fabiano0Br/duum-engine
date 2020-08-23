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
MV=$(shell cp -r ../res/ ../bin/ $<)
WMV=$(shell cp -r ../res/ ../winbin/ &<)
OPT=O3

ifdef CLANG
	CC=clang
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
	${CC} -o ${OUT} ${OJS} ./png/lodepng.c -pedantic -Wall -Wextra -${OPT} ${FLAGS} 
	${CC} -o ${BINPATH} ./launcher/main.c -${OPT}
	${MV}
	@echo Build Done! Check ${OUT}
