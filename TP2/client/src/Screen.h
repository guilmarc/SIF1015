//
// Created by Nicolas Boisvert on 16-11-20.
//

#ifndef SIF1015_SCREEN_H
#define SIF1015_SCREEN_H

#include <ncurses.h>
#include "ScreenDimensions.h"

typedef struct {
    WINDOW* window;
    ScreenDimensions dimensions;
    char* label;
    int colorSet;
} Screen;

Screen* createScreen(ScreenDimensions dimensions, char* label, int colorSet);
void showScreen(Screen* screen);
void printTitle(Screen* screen);
#endif //SIF1015_SCREEN_H
