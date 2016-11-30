#include "transmissioncontroller.h"

TransmissionController::TransmissionController(std::string name) : BaseController(name)
{
    this->getFifo()->test();
}

int TransmissionController::send(char message[200])
{
    Transaction transaction = prepareTransaction(message);
    this->getFifo()->openInWrite();
    this->pushMessageToContext("Sending...");
    if(this->getFifo()->writeTransaction(transaction) < 0) {
        this->pushMessageToContext("(!) -> Unable to write transaction");
        return -1;
    }
    this->pushMessageToContext("Sent");
    this->getFifo()->closeFifo();
    return 0;
}

void TransmissionController::pushMessageToContext(QString message)
{
    this->getContext()->pushTransmissionResponse(message);
}


