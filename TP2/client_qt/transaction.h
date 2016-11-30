#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <cstring>
#include <string>
#include <unistd.h>
#include <sys/types.h>

struct Transaction {
    pid_t pid_client;
    int status_code;
    char transaction[200];
};

void printTransaction(Transaction transaction);
Transaction prepareTransaction(char message[200]);
#endif // TRANSACTION_H
