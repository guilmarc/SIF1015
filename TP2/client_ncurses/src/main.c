//
// Created by Nicolas Boisvert on 16-11-20.
//

#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#include <ctype.h>
#include <panel.h>
#include "screen_dimensions.h"
#include "user.h"
#include "screen.h"
#include "client.h"

#define SPLITTED_WINDOWS 2
#define GREEN_WINDOW 1
#define CYAN_WINDOW 1

int login();
void initialize();
int transmitLogin();
int sendTransaction(char* transactionContent);
User *user;

int main() {
    initialize();
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
    }*/
    endwin();
    return 0;
}

int transmitLogin() {
    char transaction[200] = "";
    login();
    userAddCommand(*user, transaction);
    if (strcmp(transaction, "") == 0) {
        printf("Transaction not created\n");
        return -1;
    }
    return sendTransaction(transaction);
}
void initialize() {
    if (transmitLogin() != 0) {
        printf("Login was unsuccessful\n");
        exit(EXIT_FAILURE);
    };
    printf("Login as %s\n", user->nickname);
    char message[200] = "";
    while(strcmp(message, "quit") != 0) {
        printf("Command : ");
        scanf("%s", message);
        sendTransaction(message);
    }
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
}

int sendTransaction(char* transactionContent) {
    int serverFifoFd,
            clientFifoFd;
    char clientFifo[256];
    Info_FIFO_Transaction transaction = createTransaction(transactionContent);
    printf("%s", transactionContent);

    serverFifoFd = open(SERVER_FIFO_NAME, O_WRONLY);
    if (serverFifoFd == -1) {
        fprintf(stderr, "Sorry, no server\n");
        return -1;
    }
    sprintf(clientFifo, CLIENT_FIFO_NAME, transaction.pid_client);
    if (mkfifo(clientFifo, 0777) == -1) {
        fprintf(stderr, "Sorry, can't make %s\n", clientFifo);
        return -1;
    }
    write(serverFifoFd, &transaction, sizeof(transaction));
    clientFifoFd = open(clientFifo, O_RDONLY);
    if (clientFifoFd != -1) {
        if (read(clientFifoFd, &transaction, sizeof(transaction)) > 0) {
            printf("received: %s\n", transaction.transaction);
        }
        close(clientFifoFd);
    }
    close(serverFifoFd);
    unlink(clientFifo);
    return 0;
}

int login() {
    initscr();
    WINDOW* win = createScreen(getSplitScreenDimensions(1, 0), "Title", 1)->window;
    user = malloc(sizeof(User));
    user->nickname = promptForStringResponse(win, "Enter your nickname :", 0);
    user->speciality = promptForStringResponse(win, "Enter your speciality :", 1);
    user->scholarships = promptForStringResponse(win, "Enter your scholarships :", 2);
    user->experiences = atoi(promptForStringResponse(win, "Enter your experiences :", 3));
    delwin(win);
    endwin();
    return 0;
}

