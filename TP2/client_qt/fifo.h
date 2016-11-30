#ifndef FIFO_H
#define FIFO_H

#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <fcntl.h>
#include <limits.h>
#include <sys/stat.h>
#include "transaction.h"

class Fifo
{
private:
    int descriptor;
    std::string name;
    void setDescriptor(int descriptor);
    void setName(std::string name);
    int openFifo(int permission);
public:
    Fifo();
    Fifo(std::string name);
    int openInRead();
    int openInWrite();
    int closeFifo();
    bool isOpen();
    int test();
    int create();
    int writeTransaction(Transaction transaction);
    Transaction readTransaction();
    int destroy();
    int getDescriptor();
    std::string getName();
    char* getNameCStr();
};

#endif // FIFO_H
