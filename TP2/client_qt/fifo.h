#ifndef FIFO_H
#define FIFO_H

#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/stat.h>

class Fifo
{
private:
    int descriptor;
    char* name;
    void setDescriptor(int descriptor);
    void setName(char* name);
    int openFifo(int permission);
public:
    Fifo();
    Fifo(char* name);
    int openInRead();
    int openInWrite();
    int closeFifo();
    bool isOpen();
    int create();
    int destroy();
    int getDescriptor();
    char* getName();
};

#endif // FIFO_H
