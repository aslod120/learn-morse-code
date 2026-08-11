#include "UIButtons.h"

Color UI_stateToColor(int state)
{
    switch (state)
    {
    case 0:
        return DEFAULT;
        break;
    case 1:
        return HOVERING;
        break;
    case 2:
        return SELECTED;
        break;
    
    default:
        return DEFAULT;
        break;
    }
}

bool drawButton(Rectangle rect, const char *text, float size)
{
    bool result = false;
    int state = 0;

    if(CheckCollisionPointRec(GetMousePosition(), rect))
    {
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){state = 2;}
        else {state = 1;}

        if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){result = true;}
    }

    // draw the button
    DrawRectangleRec(rect, UI_stateToColor(state));
    DrawText(text, rect.x, rect.y, size, BLACK);

    return result;
}