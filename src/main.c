#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "main.h"
#include "linked_list.h"
#include "member.h"
#include "main.h"

const char FILEPATH[] = "trans2.txt";
const char FILEOPEN_METHOD[] = "r";
const int MAX_BUFFER_SIZE = 1024;

int main(int argc, char **argv) {
    parseCommand("A Tidge 2001");
    return 0;
}

void loadFile(Node* headNode) {
    //FILE *file = fopen(FILEPATH, FILEOPEN_METHOD);
}

int parseCommand(char commandString[]) {
    char command = toupper(commandString[0]);
    switch (command) {
        case 'A':
            break;
        case 'M':
            break;
        case 'E':
            break;
        case 'L':
            break;
        default:
            printf("Undefined command \'%c\'\n", command);
            return -1;
            break;
    }
    return 0;
}
