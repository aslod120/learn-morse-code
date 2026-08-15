#include "bitbyte.h"

#define ALL_LETTERS (67108863U)

void engine_morseUpdate();
void engine_morseDraw();
void engine_settingsUpdate();
void engine_settingsDraw();

states engine_state;

char characterToPlay;
char *characterCode;
char userInput;
bool userAnswered;
bool userAnsweredCorrectly;

Font profaFont;
float fontSize;

int WPM;

unsigned int selectedLetters;
unsigned int newSelectedLetters;

bool adaptiveLearning;
bool alwaysShowMorseCode;
bool noSelectedLetters;

// variable initialization function
void engine_init()
{
    engine_state = morseCode;
    selectedLetters = ALL_LETTERS; // turn on all the bits
    newSelectedLetters = 0;
    audio_init();
    data_init();
    play_init();
    flashcard_init();
    flashcard_shuffleDeck(1);

    WPM = 10;
    play_setWPM(WPM);

    // downloaded from (https://www.dafont.com/profa.font)
    profaFont = LoadFont("./fonts/ProfaTrial-Black.ttf");
    fontSize = profaFont.baseSize;
    if(IsFontValid(profaFont) == false)
    {
        profaFont = GetFontDefault();
        fontSize = 30;
    }

    characterToPlay = flashcard_getCard();
    characterCode = data_get(characterToPlay);
    userAnswered = false;
    userAnsweredCorrectly = false;

    adaptiveLearning = false;
    alwaysShowMorseCode = false;
    noSelectedLetters = false;
}

// update function
void engine_update()
{
    if(engine_state == morseCode)
    {
        engine_morseUpdate();
    }
    else if(engine_state == settings)
    {
        engine_settingsUpdate();
    }
}

// drawing function
void engine_draw()
{
    ClearBackground(BACKGROUND);

    if(engine_state == morseCode)
    {
        engine_morseDraw();
    }
    else if(engine_state == settings)
    {
        engine_settingsDraw();
    }

    #ifdef DEBUG
    if(IsKeyDown(KEY_TAB))
    {
        flashcard_debug(20);
        DrawText(TextFormat("Current Letter: %c", characterToPlay), 0, 480, 20, GREEN);
    }
    #endif
}

void engine_uninitialize()
{
    audio_uninitialize();
}

void engine_morseUpdate()
{
    audio_update();
    play_update();

    if(IsKeyPressed(KEY_SPACE))
    {
        play_startChar(characterToPlay);
    }
    if(IsKeyPressed(KEY_ENTER) && userAnswered == true)
    {
        // get a new character
        characterToPlay = flashcard_getCard();
        characterCode = data_get(characterToPlay);
        userAnswered = false;
    }

    userInput = GetCharPressed();
    while(userInput > 0)
    {
        if(isalpha(userInput) && userAnswered == false)
        {
            userAnsweredCorrectly = flashcard_processAnswer(userInput, characterToPlay);
            // want to stop processing answers after the player answered
            userAnswered = true;

            // if adaptive learning is turned on and box 1 and 2 are empty (meaning the user got the letters right)
            // add a new random letter to box 1
            if(adaptiveLearning == true && flashcard_boxLength(1) == 0 && flashcard_boxLength(2) == 0)
            {
                // get a new random letter here
                
            }
        }
        userInput = GetCharPressed();
    }
}
void engine_morseDraw()
{
    // settings button
    if(drawButton((Rectangle){GetScreenWidth() - 175, 50, 125, 40}, "Settings", profaFont, fontSize))
    {
        engine_state = settings;
        newSelectedLetters = selectedLetters;
    }

    // draw underline
    DrawTextEx(profaFont, "____________________", (Vector2){GetScreenWidth()/2 - 130, GetScreenHeight()/2 + 40}, fontSize, -1, RAYWHITE);
    
    // process answer
    if(userAnswered == true)
    {
        if(userAnsweredCorrectly == true)
        {
            DrawTextEx(profaFont, "Correct!", (Vector2){GetScreenWidth()/2 - 60, GetScreenHeight()/2 - 40}, fontSize, 2, GREEN);
        }
        else if(userAnsweredCorrectly == false)
        {
            DrawTextEx(profaFont, "Incorrect!", (Vector2){GetScreenWidth()/2 - 60, GetScreenHeight()/2 - 40}, fontSize, 2, RED);
        }
        //DrawText(TextFormat("Letter: %c", characterToPlay), GetScreenWidth()/2, GetScreenHeight()/2, 20, RAYWHITE);
        DrawTextEx(profaFont, TextFormat("Letter: %c", characterToPlay), (Vector2){GetScreenWidth()/2 - 60, GetScreenHeight()/2}, fontSize, 2, RAYWHITE);
        // draw the dots and dashes too
        //DrawTextEx(profaFont, TextFormat("%s", characterCode), (Vector2){GetScreenWidth()/2 - 30, GetScreenHeight()/2 + 30}, fontSize, 10, RAYWHITE);
        if(drawButton((Rectangle){GetScreenWidth()/2 - 90, GetScreenHeight()/2 + 165, 175, 50}, "Next", profaFont, fontSize))
        {
            // get a new character
            characterToPlay = flashcard_getCard();
            characterCode = data_get(characterToPlay);
            userAnswered = false;
        }
    }
    else
    {
        DrawTextEx(profaFont, "(Type a Letter)", (Vector2){GetScreenWidth()/2 - 110, GetScreenHeight()/2}, fontSize, 2, ColorAlpha(RAYWHITE, 0.2));
    }

    // show the morse code -- to do: make the font bigger
    if(alwaysShowMorseCode == true || userAnswered == true)
    {
        DrawTextEx(profaFont, TextFormat("%s", characterCode), (Vector2){GetScreenWidth()/2 - 30, GetScreenHeight()/2 + 30}, fontSize, 10, RAYWHITE);
    }

    // play audio button
    if(drawButton((Rectangle){GetScreenWidth()/2 - 90, GetScreenHeight()/2 + 100, 175, 50}, "Play Audio", profaFont, fontSize))
    {
        play_startChar(characterToPlay);
    }

    // frequency
    DrawTextEx(profaFont, "Frequency", (Vector2){40, 0}, fontSize, 2, RAYWHITE);
    DrawTextEx(profaFont, TextFormat("%d", audio_getFrequency()), (Vector2){75, 30}, fontSize, 2, RAYWHITE);
    if(drawButton((Rectangle){20, 30, 50, 50}, " -", profaFont, 30))
    {
        audio_changeFrequency(-10);
    }
    if(drawButton((Rectangle){145, 30, 50, 50}, " +", profaFont, 30))
    {
        audio_changeFrequency(10);
    }

    // WPM
    DrawTextEx(profaFont, "WPM", (Vector2){70, 90}, fontSize, 2, RAYWHITE);
    DrawTextEx(profaFont, TextFormat("%d", WPM), (Vector2){90, 120}, fontSize, 2, RAYWHITE);
    if(drawButton((Rectangle){20, 120, 50, 50}, " -", profaFont, 30))
    {
        WPM--;
        if(WPM < 5){WPM = 5;}
        play_setWPM(WPM);
    }
    if(drawButton((Rectangle){145, 120, 50, 50}, " +", profaFont, 30))
    {
        WPM++;
        if(WPM > 30){WPM = 30;}
        play_setWPM(WPM);
    }

    alwaysShowMorseCode = drawCheckbox("Always Show Morse Code", (Vector2){20, 200}, 40, alwaysShowMorseCode, 5, profaFont, fontSize);
}

void engine_settingsUpdate()
{

}
void engine_settingsDraw()
{
    if(drawButton((Rectangle){GetScreenWidth() - 175, 50, 80, 30}, "Back", profaFont, fontSize))
    {
        if(newSelectedLetters == 0)
        {
            noSelectedLetters = true;
        }
        if(noSelectedLetters == false)
        {
            // test if the character settings have changed
            if(newSelectedLetters == 0){newSelectedLetters = 1;} // fall back
            if(newSelectedLetters != selectedLetters)
            {
                // remove everything from the boxes
                flashcard_clearAllBoxes();
                // fill box 1 with the selected letters
                for(int i = 0; i < 26; i++)
                {
                    if((bool)int32GetBit(newSelectedLetters, i) == true)
                    {
                        flashcard_queue(1, i + 'A');
                    }
                }
                // get a new letter
                userAnswered = false;
                userAnsweredCorrectly = false;
                flashcard_shuffleDeck(1);
                characterToPlay = flashcard_getCard();
                characterCode = data_get(characterToPlay);

                selectedLetters = newSelectedLetters;
            }
            engine_state = morseCode;
        }
    }

    // warn the user to select a letter
    if(noSelectedLetters == true)
    {
        DrawTextEx(profaFont, "Please select a letter", (Vector2){GetScreenWidth() - 300, 100}, fontSize, -1, RAYWHITE);
        if(newSelectedLetters > 0){noSelectedLetters = false;}
    }

    if(drawButton((Rectangle){100, GetScreenHeight() - 300, 125, 40}, "Clear All", profaFont, fontSize)){newSelectedLetters = 0;}
    if(drawButton((Rectangle){100, GetScreenHeight() - 250, 140, 40}, "Select All", profaFont, fontSize)){newSelectedLetters = ALL_LETTERS;}
    //drawButton((Rectangle){100, GetScreenHeight() - 200, 190, 40}, "Easy Letters", profaFont, fontSize);
    //drawButton((Rectangle){100, GetScreenHeight() - 150, 190, 40}, "Hard Letters", profaFont, fontSize);
    //adaptiveLearning = drawCheckbox("Adaptive Learning", (Vector2){100, GetScreenHeight()/2}, 40, adaptiveLearning, 5, profaFont, fontSize);

    for(int i = 0; i < 26; i++)
    {
        if(drawCheckbox(TextFormat("%c", i + 'A'), (Vector2){50 + (i % 7) * 100, 50 + (int)(i/7) * 75}, 50, (bool)int32GetBit(newSelectedLetters, i), 5, profaFont, fontSize) == true)
        {
            newSelectedLetters = int32SetBit(newSelectedLetters, i);
        }
        else
        {
            newSelectedLetters = int32RemoveBit(newSelectedLetters, i);
        }
    }
}