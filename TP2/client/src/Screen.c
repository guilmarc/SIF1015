//
// Created by Nicolas Boisvert on 16-11-20.
//

#include <stdlib.h>
#include "Screen.h"
#include <string.h>
#include "ScreenDimensions.h"
#include <ncurses.h>

Screen* createScreen(ScreenDimensions dimensions, char* label, int colorSet) {
    Screen* screen = malloc(sizeof(Screen));
    screen->window = newwin(dimensions.height, dimensions.width, dimensions.y, dimensions.x);
    screen->dimensions = dimensions;
    screen->label = label;
    screen->colorSet = colorSet;
    return screen;
}

void showScreen(Screen* screen) {
    getbegyx(screen->window, screen->dimensions.y, screen->dimensions.x);
    getmaxyx(screen->window, screen->dimensions.height, screen->dimensions.width);

    box(screen->window, 0, 0);
    wrefresh(screen->window);
    mvwaddch(screen->window, 2, 0, ACS_LTEE);
    mvwhline(screen->window, 2, 1, ACS_HLINE, screen->dimensions.width - 2);
    mvwaddch(screen->window, 2, screen->dimensions.width - 1, ACS_RTEE);

    printTitle(screen);
}

void printTitle(Screen* screen) {
    int length, x, y;
    float temp;

    if(screen->window == NULL) {
        screen->window = stdscr;
    }
    getyx(screen->window, y, x);
    if(screen->dimensions.x != 0) {
        x = screen->dimensions.x;
    }
    if(screen->dimensions.y != 0) {
        y = screen->dimensions.y;
    }
    if(screen->dimensions.width == 0) {
        screen->dimensions.width = 80;
    }

    length = strlen(screen->label);
    temp = (screen->dimensions.width - length)/ 2;
    x = screen->dimensions.x + (int)temp;
    wattron(screen->window, screen->colorSet);
    mvwprintw(screen->window, y, x, "%s", screen->label);
    wattroff(screen->window, screen->colorSet);
    refresh();
}