#include "bitbyte.h"

// encasing in if defined to do away with the squiggly red line
#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
const int screenWidth = 1280;
const int screenHeight = 720;

char characterToPlay;
char userInput;
bool userAnswered;
bool userAnsweredCorrectly;

Font profaFont;
float fontSize;

int WPM;

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------
void UpdateGame(void);     // Update and Draw one frame

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "Learn Morse Code");
    
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
        fontSize = 20;
    }

    characterToPlay = flashcard_getCard();
    userAnswered = false;
    userAnsweredCorrectly = false;
    
    // add debug stuff here
    

    #if defined(PLATFORM_WEB)
        emscripten_set_main_loop(UpdateGame, 0, 1);
    #else
        SetTargetFPS(60);
        while(!WindowShouldClose())
        {
            UpdateGame();
        }
    #endif


    // De-Initialization
    //--------------------------------------------------------------------------------------
    audio_uninitialize();
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

//----------------------------------------------------------------------------------
// Module Functions Definition
//----------------------------------------------------------------------------------
void UpdateGame(void)
{
    
    // Update
    //----------------------------------------------------------------------------------
    // TODO: Update your variables here
    //----------------------------------------------------------------------------------
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
        }
        userInput = GetCharPressed();
    }

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

        ClearBackground(BLACK);

        //DrawText(TextFormat("Letter: %c", characterToPlay), screenWidth/2, screenHeight/2, 20, BLACK);
        if(userAnswered == true)
        {
            if(userAnsweredCorrectly == true)
            {
                //DrawText("Correct!", screenWidth/2, screenHeight/2 - 40, 20, GREEN);
                DrawTextEx(profaFont, "Correct!", (Vector2){screenWidth/2, screenHeight/2 - 40}, fontSize, 2, GREEN);
            }
            else if(userAnsweredCorrectly == false)
            {
                //DrawText("Incorrect!", screenWidth/2, screenHeight/2 - 40, 20, RED);
                DrawTextEx(profaFont, "Incorrect!", (Vector2){screenWidth/2, screenHeight/2 - 40}, fontSize, 2, RED);
            }
            //DrawText(TextFormat("Letter: %c", characterToPlay), screenWidth/2, screenHeight/2, 20, RAYWHITE);
            DrawTextEx(profaFont, TextFormat("Letter: %c", characterToPlay), (Vector2){screenWidth/2, screenHeight/2}, fontSize, 2, RAYWHITE);
        }

        // draw buttons here
        // frequency
        DrawTextEx(profaFont, "Frequency", (Vector2){40, 0}, fontSize, 2, RAYWHITE);
        DrawTextEx(profaFont, TextFormat("%d", audio_getFrequency()), (Vector2){75, 30}, fontSize, 2, RAYWHITE);
        if(drawButton((Rectangle){20, 30, 50, 50}, " -", 30))
        {
            audio_changeFrequency(-10);
        }
        if(drawButton((Rectangle){145, 30, 50, 50}, " +", 30))
        {
            audio_changeFrequency(10);
        }
        // WPM
        
        DrawTextEx(profaFont, "WPM", (Vector2){70, 90}, fontSize, 2, RAYWHITE);
        
        DrawTextEx(profaFont, TextFormat("%d", WPM), (Vector2){90, 120}, fontSize, 2, RAYWHITE);
        if(drawButton((Rectangle){20, 120, 50, 50}, " -", 30))
        {
            WPM--;
            if(WPM < 5){WPM = 5;}
            play_setWPM(WPM);
        }
        if(drawButton((Rectangle){145, 120, 50, 50}, " +", 30))
        {
            WPM++;
            if(WPM > 30){WPM = 30;}
            play_setWPM(WPM);
        }

        //flashcard_debug(20);


    EndDrawing();
    //----------------------------------------------------------------------------------
}