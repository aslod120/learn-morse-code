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
    
    engine_init();
    

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
    engine_uninitialize();
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
    engine_update();

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

        engine_draw();

    EndDrawing();
    //----------------------------------------------------------------------------------
}