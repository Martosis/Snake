SOURCES := $(shell find src -name '*.cpp')

all:
	g++ -Iinclude -Llib -o main ${SOURCES} -lmingw32 -lSDL2main -lSDL2 -lSDL2_image