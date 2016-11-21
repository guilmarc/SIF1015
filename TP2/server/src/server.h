//
// Created by Marco Guillemette on 2016-11-20.
//

#ifndef SIF1015_SERVER_H
#define SIF1015_SERVER_H

typedef struct {
    char* client_fifo;
    void* data;
} SendTransactionParams;

void startServer();

void* sendTransaction(void* data);

#endif //SIF1015_SERVER_H
