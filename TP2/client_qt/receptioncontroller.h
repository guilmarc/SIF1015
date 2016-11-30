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
    ReceptionController(std::string name);
    void initRead();
    static void* readMessages(void* data);
    void pushMessageToContext(QString message);
};

#endif // RECEPTIONCONTROLLER_H
