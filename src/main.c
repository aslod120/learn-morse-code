#include "bitbyte.h"

// encasing in if defined to do away with the squiggly red line
#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
const int screenWidth = 800;
const int screenHeight = 450;

char characterToPlay;

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
    play_init(.2);
    
    // add debug stuff here
    /*
    for(char i = 'a'; i <= 'z'; i++)
    {
        printf("%c: %s\n", i, data_get(i));
    }
    for(char i = '0'; i <= '9'; i++)
    {
        printf("%c: %s\n", i, data_get(i));
    }
    */
    
    characterToPlay = 'A';

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

    if(IsKeyPressed(KEY_UP))
    {
        characterToPlay++;
        if(characterToPlay > 'Z')
        {
            characterToPlay = 'A';
        }
    }
    if(IsKeyPressed(KEY_DOWN))
    {
        characterToPlay--;
        if(characterToPlay < 'A')
        {
            characterToPlay = 'Z';
        }
    }

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText(TextFormat("Letter: %c", characterToPlay), screenWidth/2, screenHeight/2, 20, BLACK);

    EndDrawing();
    //----------------------------------------------------------------------------------
}