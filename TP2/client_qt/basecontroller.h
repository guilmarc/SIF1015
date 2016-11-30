#ifndef BASECONTROLLER_H
#define BASECONTROLLER_H

#include "messagableinterface.h"
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <fcntl.h>
#include <limits.h>
#include <sys/stat.h>
#include "fifo.h"

#define SERVER_FIFO_NAME "../../../tmp/FIFO_TRANSACTIONS"
#define CLIENT_FIFO_NAME "../../../tmp/cli_%d_fifo"

class BaseController
{
private:
    MessagableInterface* context;
    Fifo* fifo;
    void setFifo(Fifo* fifo);
public:
    BaseController(std::string name);
    Fifo* getFifo();
    void setContext(MessagableInterface* context);
    MessagableInterface* getContext();
    bool hasContext();
    static std::string getQualifiedClienFifoName(int pid);
};

#endif // BASECONTROLLER_H
