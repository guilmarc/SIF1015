#include "transaction.h"

void printTransaction(Transaction transaction)
{
    fprintf(stderr, "\nTRANSACTION\n-\tPID: %i;\n-\tContent: %s;\n\n", transaction.pid_client, transaction.transaction);
}

Transaction prepareTransaction(char message[200])
{
    Transaction transaction;
    transaction.status_code = 0;
    transaction.pid_client = getpid();
    strcpy(transaction.transaction, message);
    return transaction;
}
