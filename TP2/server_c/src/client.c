//
// Created by Marco Guillemette on 2016-11-20.
//

#include "client.h"


Info_FIFO_Transaction createTransaction(char* message) {
    Info_FIFO_Transaction transaction;
    transaction.pid_client = getpid();
    transaction.status_code = 0;
    strcpy(transaction.transaction, message);
    return transaction;
}