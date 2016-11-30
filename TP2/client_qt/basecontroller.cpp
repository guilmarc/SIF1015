#include "basecontroller.h"

BaseController::BaseController(std::string name)
{
    this->fifo = new Fifo(name.c_str());
    this->context = NULL;
}

MessagableInterface* BaseController::getContext()
{
    return this->context;
}

void BaseController::setContext(MessagableInterface* context)
{
    this->context = context;
}

Fifo* BaseController::getFifo()
{
    return this->fifo;
}

void BaseController::setFifo(Fifo* fifo)
{
    this->fifo = fifo;
}

bool BaseController::hasContext()
{
    return this->getContext() != NULL;
}

std::string BaseController::getQualifiedClienFifoName(int pid)
{
    char nameChars[256];
    sprintf(nameChars, CLIENT_FIFO_NAME, pid);
    std::string name(nameChars);
    return name;
}
