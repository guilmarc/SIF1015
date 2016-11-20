//
// Created by Nicolas Boisvert on 16-11-20.
//

#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#include "ScreenDimensions.h"
#include "User.h"
#define SPLITTED_WINDOWS 2

int login();
WINDOW *createWindow(ScreenDimensions dimensions);
User *user;

int main() {
    login();
   /* WINDOW *transmissionWindow,
        *receptionWindow;
    char inputChar;
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    printw("Press F1 to exit");
    refresh();
    transmissionWindow = createWindow(getSplitScreenDimensions(SPLITTED_WINDOWS, 0));
    receptionWindow = createWindow(getSplitScreenDimensions(SPLITTED_WINDOWS, 1));
    while((inputChar = getch()) != KEY_F(1))
    {

    }
    endwin();*/
    printUser(*user);
    return 0;
}

char* promptForStringResponse(char* message) {
    char* response = malloc(sizeof(char[100]));
    int row,col;

    initscr();
    getmaxyx(stdscr,row,col);
    mvprintw(row/2,(col-strlen(message))/2,"%s",message);
    getstr(response);
    mvprintw(LINES - 2, 0, "You Entered: %s", response);
    getch();
    endwin();
    return response;
}

int login() {
    user = malloc(sizeof(User));
    user->nickname = promptForStringResponse("Enter your nickname :");
    user->speciality = promptForStringResponse("Enter your speciality :");
    user->speciality = promptForStringResponse("Enter your scholarships :");
    user->experiences = atoi(promptForStringResponse("Enter your experiences :"));
}

WINDOW *createWindow(ScreenDimensions dimensions)
{
    WINDOW *localWin = newwin(dimensions.height, dimensions.width, dimensions.y, dimensions.x);
    box(localWin, 0 , 0);
    wrefresh(localWin);
    return localWin;
}