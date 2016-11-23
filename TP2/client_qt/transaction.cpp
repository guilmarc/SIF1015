#include "transaction.h"

Transaction::Transaction()
{
    this->transaction = "";
}

std::string Transaction::getTransaction()
{
    return this->transaction;
}

Info_FIFO_Transaction Transaction::toTransaction()
{
    Info_FIFO_Transaction transaction;
    transaction.pid_client = this->getPidClient();
    transaction.status_code = this->getStatusCode();
    strcpy(transaction.transaction, this->getTransaction().c_str());
    return transaction;
}

int Transaction::getStatusCode()
{
    return this->status_code;
}

pid_t Transaction::getPidClient()
{
    return getpid();
}
