#include "receptioncontroller.h"

ReceptionController::ReceptionController(MessagableInterface* context)
{
    this->context = context;
    this->pushMessageToContext("Reception initialized");
}


void ReceptionController::readMessages()
{

}

void ReceptionController::initRead()
{

}

void ReceptionController::pushMessageToContext(QString message)
{
    this->context->pushReceptionResponse(message);
}
