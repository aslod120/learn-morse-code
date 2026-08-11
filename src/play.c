#include "bitbyte.h"

/*
Dit: 1 unit
Dah: 3 units
Intra-character space (the gap between dits and dahs within a character): 1 unit
Inter-character space (the gap between the characters of a word): 3 units
Word space (the gap between two words): 7 units
*/

bool play_character(const char code);

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
int wordInd; // index of word to play
bool charPause; // pause between each characters of a word
bool pause; // state to pause for the next dot/dash
bool playingAudio; // state to determine if we are playing the morse code audio
bool playingWord;
float timer; // how long we should play the sine wave audio for

char wordToPlay[20];


// the smaller the speed is, the faster the words
void play_init()
{
    baseUnit = 1;
    baseDit = baseUnit;
    baseDah = baseUnit * 3;
    baseToneSpace = baseUnit;
    baseCharSpace = baseUnit * 3;
    baseWordSpace = baseUnit * 7;
    timer = 0;

    ind = 0;
    wordInd = 0;
    charPause = false;
    pause = false;
    playingAudio = false;
    playingWord = false;
    morseCodeChar = 'a'; // default value
}

void play_setWPM(int WPM)
{
    baseUnit = 1200/((float)WPM * 1000);
    baseDit = baseUnit;
    baseDah = baseUnit * 3;
    baseToneSpace = baseUnit;
    baseCharSpace = baseUnit * 3;
    baseWordSpace = baseUnit * 7;
}

void play_startChar(char code)
{
    playingAudio = true;
    morseCodeChar = code;
    ind = 0;
    pause = false;
}

void play_startWord(char *word)
{
    wordInd = 0;
    strcpy(wordToPlay, word);
    playingWord = true;
    play_startChar(word[wordInd]);
}

void play_update()
{
    if(playingAudio == true)
    {
        play_character(morseCodeChar);
    }
    if(playingAudio == false && playingWord == true)
    {
        // letter stopped but we are still in the word
        timer += GetFrameTime();
        if(wordToPlay[wordInd + 1] == '\0')
        {
            playingWord = false;
            timer = 0;
        }
        if(timer >= baseCharSpace)
        {
            wordInd++;
            timer = 0;
            play_startChar(wordToPlay[wordInd]);
        }
    }
}

// returns true if it is done playing the character, false if not
bool play_character(const char code)
{
    //printf("%d : %f\n", ind, GetTime());
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
        if(morseCodeStr[ind + 1] == '\0')
        {
            pause = false;
            ind = 0;
            playingAudio = false;
            timer = 0;
            return true;
        }

        if(timer >= baseToneSpace)
        {
            timer = 0;
            pause = false;
            ind++;
        }
    }

    return false;

}