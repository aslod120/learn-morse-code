/*******************************************************************************************
*
*   raylib [audio] example - raw stream
*
*   Example complexity rating: [★★★☆] 3/4
*
*   Example originally created with raylib 1.6, last time updated with raylib 6.0
*
*   Example created by Ramon Santamaria (@raysan5) and reviewed by James Hofmann (@triplefox)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2015-2026 Ramon Santamaria (@raysan5) and James Hofmann (@triplefox)
*
********************************************************************************************/

#include "bitbyte.h"
#include <math.h> // PI, sinf

#define BUFFER_SIZE 4096
#define SAMPLE_RATE 44100

int sineFrequency;
int sineIndex;
double sineStartTime;
float buffer[BUFFER_SIZE];
AudioStream stream;

void audio_init()
{
    InitAudioDevice();
    SetAudioStreamBufferSizeDefault(BUFFER_SIZE);
    stream = LoadAudioStream(SAMPLE_RATE, 32, 1);
    SetAudioStreamPan(stream, 0);
    PlayAudioStream(stream);
    PauseAudioStream(stream);
    sineFrequency = 500;
    sineIndex = 0;
    sineStartTime = 0;
}

void audio_uninitialize()
{
    CloseAudioDevice();
    UnloadAudioStream(stream);
}

void audio_update()
{
    if(IsAudioStreamProcessed(stream))
    {
        for(int i = 0; i < BUFFER_SIZE; i++)
        {
            int wavelength = SAMPLE_RATE/sineFrequency;
            buffer[i] = sinf(2 * PI * sineIndex/wavelength);
            sineIndex++;
            if(sineIndex >= wavelength)
            {
                sineIndex = 0;
                sineStartTime = GetTime();
            }
        }
        UpdateAudioStream(stream, buffer, BUFFER_SIZE);
    }
}

void audio_play()
{
    if(IsAudioStreamPlaying(stream) == false)
    {
        ResumeAudioStream(stream);
    }
}

void audio_stop()
{
    if(IsAudioStreamPlaying(stream) == true)
    {
        PauseAudioStream(stream);
    }
}

void audio_changeFrequency(int amount)
{
    StopAudioStream(stream);
    sineFrequency += amount;
    if(sineFrequency < 400){sineFrequency = 400;}
    if(sineFrequency > 700){sineFrequency = 700;}

    PlayAudioStream(stream);
    PauseAudioStream(stream);
}

int audio_getFrequency()
{
    return sineFrequency;
}