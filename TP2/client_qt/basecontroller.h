#ifndef BASECONTROLLER_H
#define BASECONTROLLER_H

#include "messagableinterface.h"
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/stat.h>

#ifdef Q_OS_MAC
#define SERVER_FIFO_NAME "../../../tmp/FIFO_TRANSACTIONS"
#define CLIENT_FIFO_NAME "../../../tmp/cli_%d_fifo"
#else
#define SERVER_FIFO_NAME "./tmp/FIFO_TRANSACTIONS"
#define CLIENT_FIFO_NAME "./tmp/cli_%d_fifo"
#endif

class BaseController
{
private:
    int pid;
    MessagableInterface* context;
    int serverFileDescriptor = -1;
    int clientFileDescriptor = -1;
    char* clientFifoName;
public:
    BaseController();
    BaseController(MessagableInterface* context);
    void setContext(MessagableInterface* context);
    int openServerDescriptor();
    bool serverDescriptorIsOpen();
    bool clientDescriptorIsOpen();
    int openClientDescriptor();
    int closeServerDescriptor();
    int closeClientDescriptor();
    int createClientFifo();
    int removeClientFifo();
    int getServerFileDescriptor();
    int getClientFileDescriptor();
    char* getClientFifoName();
    int getPid();
    int refreshPid();
    MessagableInterface* getContext();
};

#endif // BASECONTROLLER_H
