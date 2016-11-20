//
// Created by Nicolas Boisvert on 16-11-20.
//

#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#include <panel.h>
#include "ScreenDimensions.h"
#include "User.h"
#include "Screen.h"

#define SPLITTED_WINDOWS 2
#define GREEN_WINDOW 1
#define CYAN_WINDOW 1

int login();
void initialize();
void transmitLogin();
char* promptForStringResponse(char* message, int index);
User *user;

int main() {
    initialize();
    char* str;
    userAddCommand(*user, str);
    printf(str);
    /*Screen* screens[2];
    char inputChar;
    printw("Logged as %s, press F1 to exit", user->nickname);
    refresh();
    screens[0] = createScreen(getSplitScreenDimensions(SPLITTED_WINDOWS, 0), "Transmission", GREEN_WINDOW);
    screens[1] = createScreen(getSplitScreenDimensions(SPLITTED_WINDOWS, 1), "Reception", CYAN_WINDOW);
    showScreen(screens[0]);
    showScreen(screens[1]);
    while((inputChar = getch()) != KEY_F(1))
    {
    }
    endwin();*/
    return 0;
}

void transmitLogin() {

}

void initialize() {
    login();
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    init_pair(GREEN_WINDOW, COLOR_GREEN, COLOR_BLACK);
    init_pair(CYAN_WINDOW, COLOR_CYAN, COLOR_BLACK);
}


char* promptForStringResponse(char* message, int index) {
    char* response = malloc(sizeof(char[100]));
    int row,col;
    getmaxyx(stdscr,row,col);
    mvprintw(row/2 + index, (col-strlen(message))/2,"%s", message);
    getstr(response);
    return response;
}

int login() {
    initscr();
    user = malloc(sizeof(User));
    user->nickname = promptForStringResponse("Enter your nickname :", 0);
    user->speciality = promptForStringResponse("Enter your speciality :", 1);
    user->scholarships = promptForStringResponse("Enter your scholarships :", 2);
    user->experiences = atoi(promptForStringResponse("Enter your experiences :", 3));
    endwin();
    return 0;
}

