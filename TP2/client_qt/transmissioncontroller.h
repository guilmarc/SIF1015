#ifndef TRANSMISSIONCONTROLLER_H
#define TRANSMISSIONCONTROLLER_H
#include "messagableinterface.h"
#include "transaction.h"
#include "basecontroller.h"


class TransmissionController : public BaseController
{
public:
    TransmissionController(std::string name);
    int send(char message[200]);
    void pushMessageToContext(QString message);
};

#endif // TRANSMISSIONCONTROLLER_H
