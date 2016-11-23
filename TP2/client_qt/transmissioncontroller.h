#ifndef TRANSMISSIONCONTROLLER_H
#define TRANSMISSIONCONTROLLER_H
#include "messagableinterface.h"
#include "transaction.h"
#include "basecontroller.h"


class TransmissionController : public BaseController
{
public:
    TransmissionController();
    TransmissionController(MessagableInterface* context);
    int send(char message[200]);
    Info_FIFO_Transaction prepareTransaction(char message[200]);
    void connectToFifo();
    void printTransaction(Info_FIFO_Transaction transaction);
    void pushMessageToContext(QString message);
};

#endif // TRANSMISSIONCONTROLLER_H
