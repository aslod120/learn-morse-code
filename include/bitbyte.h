#ifndef BITBYTE
#define BITBYTE

#include "raylib.h"
#include <math.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// ## audio ##
void audio_init();
void audio_update();
void audio_play();
void audio_stop();

// ## data ##
void data_init();
char* data_get(char code);

// ## play ##
void play_init(float speed);
void play_update();
void play_startChar(char code);
void play_startWord(char *word);

#endif