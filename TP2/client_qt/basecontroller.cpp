#include "basecontroller.h"
BaseController::BaseController()
{
    this->refreshPid();
    this->serverFileDescriptor = -1;
    this->clientFileDescriptor = -1;
}

BaseController::BaseController(MessagableInterface* context)
{
    this->setContext(context);
    this->refreshPid();
    this->serverFileDescriptor = -1;
    this->clientFileDescriptor = -1;
}

bool BaseController::serverDescriptorIsOpen()
{
    return (this->getServerFileDescriptor() > 0);
}

bool BaseController::clientDescriptorIsOpen()
{
    return (this->getClientFileDescriptor() > 0);
}

int BaseController::createClientFifo()
{
    int returnCode;
    strcpy(this->clientFifoName, "");
    sprintf(this->clientFifoName, CLIENT_FIFO_NAME, this->getPid());
    if ((returnCode = mkfifo(this->clientFifoName, 0777)) == -1) {
        fprintf(stderr, "Sorry, can't make %s\n", this->clientFifoName);
    }
    return returnCode;
}

int BaseController::getPid()
{
    return this->pid;
}

int BaseController::refreshPid()
{
    this->pid = getpid();
    return this->getPid();
}

int BaseController::openServerDescriptor()
{
    fprintf(stderr, "Check if open\n");
    if (this->serverDescriptorIsOpen()) {
        fprintf(stderr, "Is open\n");
        this->closeServerDescriptor();
    }
    fprintf(stderr, "Attempting to open\n");
    this->serverFileDescriptor = open(SERVER_FIFO_NAME, O_WRONLY);
    if (!this->serverDescriptorIsOpen()) {
        fprintf(stderr, "Sorry, no server %i \n", this->getServerFileDescriptor());
        return -1;
    }
    return this->serverFileDescriptor;
}

void BaseController::setContext(MessagableInterface* context)
{
    this->context = context;
}

int BaseController::openClientDescriptor()
{
    if (this->clientDescriptorIsOpen()) {
        return this->closeClientDescriptor();
    }
    this->clientFileDescriptor = open(this->clientFifoName, O_RDONLY);
    if(!this->clientDescriptorIsOpen()) {
        fprintf(stderr, "Sorry, can't open personnal fifo\n");
        return -1;
    }
    return this->clientFileDescriptor;
}

int BaseController::closeServerDescriptor()
{
    if (this->serverDescriptorIsOpen()) {
        return close(this->serverFileDescriptor);
    }
    return 0;
}

int BaseController::closeClientDescriptor()
{
    if (this->clientDescriptorIsOpen()) {
        return close(this->clientFileDescriptor);
    }
    return 0;
}

int BaseController::removeClientFifo()
{
    if (this->clientDescriptorIsOpen()) {
        this->closeClientDescriptor();
    }
    return unlink(this->clientFifoName);
}

char* BaseController::getClientFifoName()
{
    return this->clientFifoName;
}

int BaseController::getServerFileDescriptor()
{
    return this->serverFileDescriptor;
}

int BaseController::getClientFileDescriptor()
{
    return this->clientFileDescriptor;
}

MessagableInterface* BaseController::getContext()
{
    return this->context;
}
