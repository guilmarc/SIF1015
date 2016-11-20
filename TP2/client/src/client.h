//
// Created by Marco Guillemette on 2016-11-20.
//

#ifndef SIF1015_CLIENT_H
#define SIF1015_CLIENT_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>

#define SERVER_FIFO_NAME "./tmp/serv_fifo"
#define CLIENT_FIFO_NAME "./tmp/cli_%d_fifo"


typedef struct { //Va s'appeler transaction dans le TP
    pid_t  pid_client;
    char   transaction[200];
} Info_FIFO_Transaction;


#endif //SIF1015_CLIENT_H

