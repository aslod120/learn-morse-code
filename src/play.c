#include "bitbyte.h"

/*
Dit: 1 unit
Dah: 3 units
Intra-character space (the gap between dits and dahs within a character): 1 unit
Inter-character space (the gap between the characters of a word): 3 units
Word space (the gap between two words): 7 units
*/

void play_character(const char code);

// units for how long each part should persist
float baseUnit;
float baseDit;
float baseDah;
float baseToneSpace;
float baseCharSpace;
float baseWordSpace;

// public vars to track the audio processing
char morseCodeChar; // the character we are going to play
char *morseCodeStr; // the string of morse code in data.c
int ind; // the index of the morse code string in data.c
bool pause; // state to pause for the next dot/dash
bool playingAudio; // state to determine if we are playing the morse code audio
float timer; // how long we should play the sine wave audio for


// the smaller the speed is, the faster the words
void play_init(float speed)
{
    baseUnit = speed;
    baseDit = baseUnit;
    baseDah = baseUnit * 3;
    baseToneSpace = baseUnit;
    baseWordSpace = baseUnit * 7;
    timer = 0;

    ind = 0;
    pause = false;
    playingAudio = false;
    morseCodeChar = 'a'; // default value
}

void play_start(char code)
{
    playingAudio = true;
    morseCodeChar = code;
    ind = 0;
    pause = false;
}

bool play_isPlaying()
{
    return playingAudio;
}

void play_update()
{
    if(playingAudio == true)
    {
        play_character(morseCodeChar);
    }

}

// play the letter a
void play_character(const char code)
{
    // dot, wait, dash
    morseCodeStr = data_get(code);
    if(morseCodeStr[ind] != '\0' && pause == false)
    {
        audio_play();
        timer += GetFrameTime();
        if(morseCodeStr[ind] == 's' && timer >= baseDit) // dot
        {
            audio_stop();
            pause = true;
            timer = 0;
        }
        if(morseCodeStr[ind] == 'l' && timer >= baseDah) // dash
        {
            audio_stop();
            pause = true;
            timer = 0;
        }
    }

    if(pause == true)
    {
        timer += GetFrameTime();
        if(timer >= baseToneSpace)
        {
            timer = 0;
            pause = false;
            ind++;
        }
    }

    if(morseCodeStr[ind] == '\0')
    {
        pause = false;
        ind = 0;
        playingAudio = false;
    }

}