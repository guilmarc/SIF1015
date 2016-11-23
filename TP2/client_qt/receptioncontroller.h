#ifndef RECEPTIONCONTROLLER_H
#define RECEPTIONCONTROLLER_H

#include <pthread.h>
#include "messagableinterface.h"
#include "transmissioncontroller.h"
#include "transaction.h"
#include "basecontroller.h"

#define CLIENT_FIFO_NAME "../../../tmp/cli_%d_fifo"

class ReceptionController : public BaseController
{
public:
    ReceptionController();
    ReceptionController(MessagableInterface* context);
    void initRead();
    void readMessages();
    void pushMessageToContext(QString message);
};

#endif // RECEPTIONCONTROLLER_H
