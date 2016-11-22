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

//#define SERVER_FIFO_NAME "~/Git/tp2/TP2/bin/tmp/FIFO_TRANSACTIONS"
//#define CLIENT_FIFO_NAME "~/Git/tp2/TP2/bin/tmp/cli_%d_fifo"

#define SERVER_FIFO_NAME "../../../tmp/FIFO_TRANSACTIONS"
#define CLIENT_FIFO_NAME "../../../tmp/cli_%d_fifo"

struct Info_FIFO_Transaction {
    pid_t pid_client;
    char transaction[200];
};

class TransmissionController
{
private:
    int pid;
public:
    TransmissionController();
    int send(char message[200]);
    Info_FIFO_Transaction prepareTransaction(char message[200]);
    int getPid();
};

#endif // TRANSMISSIONCONTROLLER_H
