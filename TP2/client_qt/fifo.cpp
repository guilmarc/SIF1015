#include "fifo.h"

Fifo::Fifo()
{
    this->setDescriptor(-1);
}

Fifo::Fifo(char* name)
{
    this->setDescriptor(-1);
    this->setName(name);
}

int Fifo::openFifo(int permission)
{
    int returnCode = open(this->getName(), permission);
    this->setDescriptor(returnCode);
    return this->getDescriptor();
}

int Fifo::openInRead()
{
    return this->openFifo(O_RDONLY);
}

int Fifo::openInWrite()
{
    return this->openFifo(O_WRONLY);
}

int Fifo::closeFifo()
{
    return close(this->getDescriptor());
}

bool Fifo::isOpen()
{
    return (this->getDescriptor() > 0);
}

int Fifo::create()
{
    return mkfifo(this->getName(), 0777);
}

int Fifo::destroy()
{
    return unlink(this->getName());
}

int Fifo::getDescriptor()
{
    return this->descriptor;
}

char* Fifo::getName()
{
    return this->name;
}

void Fifo::setName(char* name)
{
    strcpy(this->name, name);
}

void Fifo::setDescriptor(int descriptor)
{
    this->descriptor = descriptor;
}
