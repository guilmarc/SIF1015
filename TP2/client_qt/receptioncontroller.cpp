#include "receptioncontroller.h"

ReceptionController::ReceptionController(std::string name) : BaseController(name)
{
    this->getFifo()->create();
}

void* ReceptionController::readMessages(void* controllerReference)
{
    ReceptionController* thisController = (ReceptionController*)controllerReference;
    Transaction transaction;
    thisController->pushMessageToContext("Initialized");
    thisController->getFifo()->openInRead();
    while(1) {
        if (thisController->getFifo()->isOpen()) {
            if (read(thisController->getFifo()->getDescriptor(), &transaction, sizeof(transaction)) > 0) {
                thisController->pushMessageToContext(QString(transaction.transaction));
            }
        }
    }
    thisController->getFifo()->closeFifo();
    thisController->getFifo()->destroy();
}

void ReceptionController::initRead()
{
    pthread_t thread;
    pthread_create(&thread, NULL, &ReceptionController::readMessages, this);
}

void ReceptionController::pushMessageToContext(QString message)
{
    if (this->hasContext()) {
        this->getContext()->pushReceptionResponse(message);
    }
}
