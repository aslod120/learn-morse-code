# PLATFORM_DESKTOP
# PLATFORM_WEB

PLATFORM ?= PLATFORM_DESKTOP

ifeq ($(PLATFORM), PLATFORM_DESKTOP)
	CC = gcc
	SOURCES = ./src/*.c
	CFLAGS = -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm
	OUT = -o app.exe
	RUN = ./app.exe
endif

ifeq ($(PLATFORM), PLATFORM_WEB)
	CC = emcc
	# need to include each file here to compile
	SOURCES = ./src/main.c ./src/audio.c ./src/boolbits.c ./src/data.c ./src/engine.c ./src/flashcard.c ./src/play.c ./src/UIButtons.c
	CFLAGS = -Os -Wall -I include/ .\lib\libweblib.a -s USE_GLFW=3 --shell-file .\webShell\shell.html --preload-file .\fonts -DPLATFORM_WEB
	OUT = -o index.html
	RUN = emrun index.html
endif

DEBUG = -DDEBUG

all: main run clean

main:
	$(CC) $(SOURCES) $(CFLAGS) $(DEBUG) $(OUT)

run:
	$(RUN)

clean:
	