#include "transmissioncontroller.h"

TransmissionController::TransmissionController()
{
    this->pid = getpid();
}

int TransmissionController::getPid()
{
    return this->pid;
}

int TransmissionController::send(char message[200])
{
    Transaction transaction = this->prepareTransaction(message);
    int serverFifoFd,
        clientFifoFd;
    char clientFifo[256];
    serverFifoFd = open(SERVER_FIFO_NAME, O_WRONLY);
    if (serverFifoFd == -1) {
        fprintf(stderr, "Sorry, no server\n");
        return -1;
    }
    sprintf(clientFifo, CLIENT_FIFO_NAME, transaction.clientPid);
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

Transaction TransmissionController::prepareTransaction(char message[200])
{
    Transaction transaction;
    transaction.clientPid = this->getPid();
    strcmp(transaction.transaction, message);
    return transaction;
}
