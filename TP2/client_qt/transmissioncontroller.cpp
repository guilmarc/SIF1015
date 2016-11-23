#include "transmissioncontroller.h"

TransmissionController::TransmissionController(MessagableInterface* context)
{
    this->pid = getpid();
    this->context = context;
    this->pushMessageToContext("Transmission initialized");
}

int TransmissionController::getPid()
{
    return this->pid;
}

void TransmissionController::connectToFifo()
{
    int serverFifoFd;
    fprintf(stderr, "Attempting connection to server...\n");
    serverFifoFd = open(SERVER_FIFO_NAME, O_WRONLY);
    if (serverFifoFd == -1) {
        fprintf(stderr, "Sorry, no server\n");
        exit(EXIT_FAILURE);
    }
    fprintf(stderr, "Connection successful\n");
    close(serverFifoFd);
}

int TransmissionController::send(char message[200])
{
    Info_FIFO_Transaction transaction = this->prepareTransaction(message);
    printTransaction(transaction);
    int serverFifoFd,
        clientFifoFd,
        returnCode = 0;
    char clientFifo[256];
    fprintf(stderr, "Attempting connection to server...\n");
    serverFifoFd = open(SERVER_FIFO_NAME, O_WRONLY);
    if (serverFifoFd == -1) {
        fprintf(stderr, "Sorry, no server\n");
        return -1;
    }
    fprintf(stderr, "Connected\nCreating personnal FIFO\n");
    sprintf(clientFifo, CLIENT_FIFO_NAME, transaction.pid_client);
    if (mkfifo(clientFifo, 0777) == -1) {
        fprintf(stderr, "Sorry, can't make %s\n", clientFifo);
        return -1;
    }
    fprintf(stderr, "Writing transaction\n");
    this->pushMessageToContext("Sending...");
    if((returnCode = write(serverFifoFd, &transaction, sizeof(transaction))) < 0) {
        fprintf(stderr, "%i - Error while writing transaction\n", returnCode);
    }
    fprintf(stderr, "%i - Error while writing transaction\n", returnCode);

    fprintf(stderr, "Opening personnal FIFO for return...\n");
    clientFifoFd = open(clientFifo, O_RDONLY);
    if (clientFifoFd != -1) {
        fprintf(stderr, "Reading return from server...\n");
        if (read(clientFifoFd, &transaction, sizeof(transaction)) > 0) {
            printf("received: %s\n", transaction.transaction);
        }
        fprintf(stderr, "Readed\n");
        close(clientFifoFd);
    }
    this->pushMessageToContext("Sent");
    fprintf(stderr, "Written\n");
    close(serverFifoFd);
    unlink(clientFifo);
    return 0;
}

void TransmissionController::printTransaction(Info_FIFO_Transaction transaction)
{
    fprintf(stderr, "\nTRANSACTION\n-\tPID: %i;\n-\tContent: %s;\n\n", transaction.pid_client, transaction.transaction);
}

void TransmissionController::pushMessageToContext(QString message)
{
    this->context->pushTransmissionResponse(message);
}


Info_FIFO_Transaction TransmissionController::prepareTransaction(char message[200])
{
    Info_FIFO_Transaction transaction;
    transaction.status_code = 0;
    transaction.pid_client = this->getPid();
    strcpy(transaction.transaction, message);
    return transaction;
}
