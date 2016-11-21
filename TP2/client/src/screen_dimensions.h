//
// Created by Nicolas Boisvert on 16-11-20.
//

#ifndef SIF1015_SCREEN_DIMENSION_H
#define SIF1015_SCREEN_DIMENSION_H

typedef struct {
    int width;
    int height;
    int x;
    int y;
} ScreenDimensions;

void printScreenDimensions(ScreenDimensions dimensions);
ScreenDimensions createScreenDimensions(int height, int width, int x, int y);
ScreenDimensions getSplitScreenDimensions(int number, int position);

#endif //SIF1015_SCREEN_H
