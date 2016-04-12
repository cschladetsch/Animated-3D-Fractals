# sudo apt-get install libsdl2-dev
#
all: boxplorer2 shadershrink edit-cfg glsl sdl2-test


CFLAGS  = -std=c++11 -g -O2 -D_REENTRANT -I/usr/include/SDL2 -I/home/christian/Dev/boxplorer2/AntTweakBar/include -I/home/christian/Dev/boxplorer2/include -DHAVE_OPENGL -DTW_NO_LIB_PRAGMA -DTW_STATIC -D_UNIX 
LIBS    =  -lSDL2_test -L/usr/local/lib -Wl,-rpath,/usr/local/lib -lSDL2 -lm -lGL -lX11 -lSDL2main


#CFLAGS=-O2 -IGL -I/usr/include/SDL2 -IAntTweakBar/include -IAntTweakBar/src -Iinclude -DGL_GLEXT_LEGACY -DTW_NO_LIB_PRAGMA -DTW_STATIC -Wall -D_UNIX -std=c++0x -DGL_VERSION_1_5

#LDFLAGS=-lm -lGL -lX11 -lSDL2 -lSDL2main

LDFLAGS = $(LIBS)

TW_OBJS=TwBar.o TwFonts.o LoadOGL.o TwMgr.o TwEventSDL.o TwPrecomp.o TwColors.o TwOpenGL.o TwEventSDL12.o TwEventSDL13.o LoadOGLCore.o TwOpenGLCore.o TwEventSDL20.o

BX_OBJS=boxplorer2.o interpolate.o uniforms.o camera.o shader.o

boxplorer2: $(BX_OBJS) $(TW_OBJS)
	g++ $(BX_OBJS) $(TW_OBJS) -o boxplorer2 $(LDFLAGS)

sdl2-test: sdl2-test.cc
	g++ $(CFLAGS) sdl2-test.cc -o sdl2-test $(LDFLAGS)

boxplorer2.o: boxplorer2.cc default_shaders.h shader_procs.h TGA.h \
	camera.h interpolate.h uniforms.h Makefile.linux params.h \
	cfgs/menger.cfg.data/fragment.glsl
	g++ -c $(CFLAGS) boxplorer2.cc

shadershrink: shadershrink.cc shadershrink.h Makefile.linux
	g++ $(CFLAGS) shadershrink.cc -o shadershrink

edit-cfg: edit-cfg.cc Makefile.linux
	g++ $(CFLAGS) edit-cfg.cc -o edit-cfg

glsl: glsl.cc TGA.h glsl.h Makefile.linux cfgs/menger.cfg.data/fragment.glsl
	g++ $(CFLAGS) glsl.cc -o glsl

interpolate.o: interpolate.cc interpolate.h
	g++ -c $(CFLAGS) interpolate.cc

shader.o: shader.cc shader.h
	g++ -c $(CFLAGS) shader.cc

camera.o: camera.cc camera.h params.h
	g++ -c $(CFLAGS) camera.cc

uniforms.o: uniforms.cc uniforms.h
	g++ -c $(CFLAGS) uniforms.cc

TwBar.o: AntTweakBar/src/TwBar.cpp
	g++ -c $(CFLAGS) $<

TwFonts.o: AntTweakBar/src/TwFonts.cpp
	g++ -c $(CFLAGS) $<

TwMgr.o: AntTweakBar/src/TwMgr.cpp
	g++ -c $(CFLAGS) $<

TwPrecomp.o: AntTweakBar/src/TwPrecomp.cpp
	g++ -c $(CFLAGS) $<

TwColors.o: AntTweakBar/src/TwColors.cpp
	g++ -c $(CFLAGS) $<

TwOpenGLCore.o: AntTweakBar/src/TwOpenGLCore.cpp
	g++ -c $(CFLAGS) $<

LoadOGLCore.o: AntTweakBar/src/LoadOGLCore.cpp
	g++ -c $(CFLAGS) $<

TwOpenGL.o: AntTweakBar/src/TwOpenGL.cpp
	g++ -c $(CFLAGS) $<

LoadOGL.o: AntTweakBar/src/LoadOGL.cpp
	g++ -c $(CFLAGS) $<

TwEventSDL.o: AntTweakBar/src/TwEventSDL.c
	g++ -c $(CFLAGS) $<

TwEventSDL12.o: AntTweakBar/src/TwEventSDL12.c
	g++ -c $(CFLAGS) $<

TwEventSDL13.o: AntTweakBar/src/TwEventSDL13.c
	g++ -c $(CFLAGS) $<

TwEventSDL20.o: AntTweakBar/src/TwEventSDL20.c
	g++ -c $(CFLAGS) $<
