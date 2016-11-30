#ifndef MESSAGABLEINTERFACE_H
#define MESSAGABLEINTERFACE_H

#include <QString>

class MessagableInterface {
public:
    virtual void pushTransmissionResponse(QString message) = 0;
    virtual void pushReceptionResponse(QString message) = 0;
};

#endif // MESSAGABLEINTERFACE_H
