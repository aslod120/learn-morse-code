#include "raylib.h"

#define DEFAULT ((Color){235, 64, 52, 255})
#define HOVERING ((Color){166, 43, 35, 255})
#define SELECTED ((Color){235, 113, 26, 255})

Color UI_stateToColor(int state);
bool drawButton(Rectangle rect, const char *text, float size);