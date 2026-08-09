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

// ## flashcards ##
void flashcard_init();
void flashcard_shuffleDeck(int boxNumber);
int flashcard_queue(int boxNum, int card);
int flashcard_boxLength(int boxNum);
bool flashcard_processAnswer(char userInput, char answer);
char flashcard_getCard();

void flashcard_debug(float size);


#endif