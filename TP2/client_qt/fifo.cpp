#include "fifo.h"

Fifo::Fifo()
{
    this->setDescriptor(-1);
}

Fifo::Fifo(std::string name)
{
    this->setDescriptor(-1);
    this->setName(name);
}

int Fifo::openFifo(int permission)
{
    int returnCode = open(this->getName().c_str(), permission);
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
    return mkfifo(this->getName().c_str(), 0777);
}

int Fifo::destroy()
{
    return unlink(this->getName().c_str());
}

int Fifo::getDescriptor()
{
    return this->descriptor;
}

std::string Fifo::getName()
{
    return this->name;
}

int Fifo::writeTransaction(Transaction transaction)
{
    return write(this->getDescriptor(), &transaction, sizeof(transaction)) < 0;
}

int Fifo::test()
{
    int returnCode = 0;
    if (this->openInWrite() == -1) {
        fprintf(stderr, "Sorry, no server_c\n");
        returnCode = -1;
        this->closeFifo();
    }
    this->closeFifo();
    return returnCode;
}

void Fifo::setName(std::string name)
{
    this->name = name;
}

void Fifo::setDescriptor(int descriptor)
{
    this->descriptor = descriptor;
}
