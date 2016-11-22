//
// Created by Nicolas Boisvert on 16-11-20.
//

#ifndef SIF1015_SCREEN_H
#define SIF1015_SCREEN_H

#include <ncurses.h>
#include "screen_dimensions.h"

typedef struct {
    WINDOW* window;
    ScreenDimensions dimensions;
    char* label;
    int colorSet;
} Screen;

Screen* createScreen(ScreenDimensions dimensions, char* label, int colorSet);
char* promptForStringResponse(WINDOW* window, char* message, int index);

#endif //SIF1015_SCREEN_H
