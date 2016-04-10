gcc -o foo boxplorer2.cc -g -O2 -D_REENTRANT -I/usr/local/include/SDL2 -DHAVE_OPENGL -g -lSDL2_test -L/usr/local/lib -Wl,-rpath,/usr/local/lib -lSDL2 -IAntTweakBar/include -Iinclude -std=c++11
