#include "transmissioncontroller.h"

TransmissionController::TransmissionController()
{
    this->createClientFifo();
}

TransmissionController::TransmissionController(MessagableInterface* context) : BaseController(context)
{
    this->pushMessageToContext("Transmission initialized");
}

void TransmissionController::connectToFifo()
{
    fprintf(stderr, "Attempting connection to server...\n");
    if (this->openServerDescriptor() == -1) {
        fprintf(stderr, "Sorry, no server\n");
        exit(EXIT_FAILURE);
    }
    fprintf(stderr, "Connection successful\n");
    this->closeServerDescriptor();
}

int TransmissionController::send(char message[200])
{
    Info_FIFO_Transaction transaction = this->prepareTransaction(message);
    int returnCode = 0;
    this->openServerDescriptor();
    this->pushMessageToContext("Sending...");
    if((returnCode = write(this->getServerFileDescriptor(), &transaction, sizeof(transaction))) < 0) {
        this->pushMessageToContext("(!) -> Unable to write transaction");
        return -1;
    }
    if (this->openClientDescriptor() != -1) {
        if (read(this->getClientFileDescriptor(), &transaction, sizeof(transaction)) > 0) {
            printf("received: %s\n", transaction.transaction);
        }
        this->closeClientDescriptor();
    }
    this->pushMessageToContext("Sent");
    this->closeServerDescriptor();
    return 0;
}

void TransmissionController::printTransaction(Info_FIFO_Transaction transaction)
{
    fprintf(stderr, "\nTRANSACTION\n-\tPID: %i;\n-\tContent: %s;\n\n", transaction.pid_client, transaction.transaction);
}

void TransmissionController::pushMessageToContext(QString message)
{
    this->getContext()->pushTransmissionResponse(message);
}


Info_FIFO_Transaction TransmissionController::prepareTransaction(char message[200])
{
    Info_FIFO_Transaction transaction;
    transaction.status_code = 0;
    transaction.pid_client = this->getPid();
    strcpy(transaction.transaction, message);
    return transaction;
}
