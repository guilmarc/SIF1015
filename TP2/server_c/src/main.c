

#include <stdlib.h>
#include <ctype.h>

#include "server.h"
#include "linkedList.h"

//Pointeur de tete de liste
Node* head;
//Pointeur de queue de liste pour ajout rapide
Node* queue;

//sem_t head_semaphore;
//sem_t queue_semaphore;

//sem_t mutex;      /* semaphore that protects counter */


int main(int argc, char* argv[]){

    startServer();

    //Fin du programme
    exit(0);
}



