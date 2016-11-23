#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <cstring>
#include <string>
#include <unistd.h>
#include <sys/types.h>

struct Info_FIFO_Transaction {
    pid_t pid_client;
    int status_code;
    char transaction[200];
};

class Transaction
{
private:
    int status_code = 0;
    std::string transaction;
public:
    Transaction();
    std::string getTransaction();
    char* getTransactionAsCStr();
    Info_FIFO_Transaction toTransaction();
    int getStatusCode();
    pid_t getPidClient();
};

#endif // TRANSACTION_H
