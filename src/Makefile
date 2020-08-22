OJS= main.c
FLAGS= -lGL -lSDL2 -lSDL2_mixer -lglut -lm -lX11 -lGLU
LFLAGS= -lm -I../include/ -L../include/GL -L../libs/SDL2 -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -mwindows -lfreeglut -lglu32 -lopengl32 
CC= gcc
WCC = i686-w64-mingw32-gcc
WFLAGS = -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lversion -luuid
OUT=../bin/duum
WOUT=../winbin/duum.exe 
MV=$(shell cp -r ../res/ ../bin/$<)
WMV=$(shell cp -r ../res/ ../bin/$<)
linux:
	${CC} -o ${OUT} ${OJS} ./png/lodepng.c -pedantic -Wall -Wextra -O3 ${FLAGS} 
	${MV}
	@echo Build Done! Cehck ${OUT}
windows:
	${WCC} -o ${OUT} ${OJS} ./png/lodepng.c -pedantic -Wall -Wextra -O3 ${LFLAGS} ${WFLAGS} 
	${WMV}
	@echo Build Done! Check ${WOUT}
lodepng.o:
	${CC} -c ./lodepng.c
