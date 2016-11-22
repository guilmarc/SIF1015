//
// Created by Nicolas Boisvert on 16-11-20.
//

#include <stdlib.h>
#include "screen.h"
#include <string.h>
#include "screen_dimensions.h"
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
}

char* promptForStringResponse(WINDOW* window, char* message, int index) {
    char* response = malloc(sizeof(char[100]));
    int row,col;
    getmaxyx(stdscr,row,col);
    mvprintw(row/2 + index, (col-strlen(message))/2,"%s", message);
    getstr(response);
    return response;
}