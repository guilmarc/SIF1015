#ifndef TRANSMISSIONCONTROLLER_H
#define TRANSMISSIONCONTROLLER_H
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "messagableinterface.h"

#define SERVER_FIFO_NAME "../../../tmp/FIFO_TRANSACTIONS"
#define CLIENT_FIFO_NAME "../../../tmp/cli_%d_fifo"

struct Info_FIFO_Transaction {
    pid_t pid_client;
    int status_code;
    char transaction[200];
};

class TransmissionController
{
private:
    MessagableInterface* context;
    int pid;
public:
    TransmissionController(MessagableInterface* context);
    int send(char message[200]);
    Info_FIFO_Transaction prepareTransaction(char message[200]);
    void connectToFifo();
    void printTransaction(Info_FIFO_Transaction transaction);
    void pushMessageToContext(QString message);
    int getPid();
};

#endif // TRANSMISSIONCONTROLLER_H
