//
// Created by Nicolas Boisvert on 16-11-20.
//

#include "stdio.h"
#include "stdlib.h"
#include "screen_dimensions.h"
#include <ncurses.h>

ScreenDimensions getSplitScreenDimensions(int number, int position) {
    int width = COLS / number;
    return createScreenDimensions(LINES, width, (width * position), 0);
}

ScreenDimensions createScreenDimensions(int height, int width, int x, int y) {
    ScreenDimensions dimensions;
    dimensions.height = height - 1;
    dimensions.width = width;
    dimensions.x = x;
    dimensions.y = y + 1;
    return dimensions;
}

void printScreenDimensions(ScreenDimensions dimensions) {
    printw("Height : %i\nWidth: %i\nX : %i\nY: %i\n", dimensions.width, dimensions.height, dimensions.x, dimensions.y);
}