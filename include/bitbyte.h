#ifndef BITBYTE
#define BITBYTE

#include "raylib.h"
#include "UIButtons.h"
#include <math.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "boolbits.h"

#define BACKGROUND ((Color){42, 45, 46, 255})

// ## audio ##
void audio_init();
void audio_uninitialize();
void audio_update();
void audio_play();
void audio_stop();
void audio_changeFrequency(int amount);
int audio_getFrequency();

// ## data ##
void data_init();
char* data_get(char code);

// ## play ##
void play_init();
void play_setWPM(int WPM);
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
void flashcard_clearAllBoxes();

void flashcard_debug(float size);

// ## engine ##
void engine_init();
void engine_update();
void engine_draw();
void engine_uninitialize();

typedef enum states
{
    morseCode,
    settings
}states;


#endif