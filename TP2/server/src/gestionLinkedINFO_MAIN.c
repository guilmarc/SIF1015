

#include <stdlib.h>
#include <ctype.h>

#include "server.h"
#include "client.h"

#include "gestionListeChaineeLinkedINFO.h"

//Pointeur de tete de liste
Node* head;
//Pointeur de queue de liste pour ajout rapide
Node* queue;

//sem_t head_semaphore;
//sem_t queue_semaphore;

//sem_t mutex;      /* semaphore that protects counter */

int main(int argc, char* argv[]){

    int server_fifo_fd, client_fifo_fd;
    int read_res;
    ClientMessage message;
    char client_fifo[256];
    char *tmp_char_ptr;


    //La FIFO de transmission de transactions devra s’appeler FIFO_TRANSACTIONS.
    //Cette FIFO est créée par le programme serveur lors de son démarrage et est ouverte par le serveur en lecture (bloquante).
    mkfifo(SERVER_FIFO_NAME, 0777);
    server_fifo_fd = open(SERVER_FIFO_NAME, O_RDONLY);


    //Ensuite, le serveur boucle en lecture sur la FIFO FIFO_TRANSACTIONS pour lire les informations provenant des clients.
    //À chaque lecture, le serveur lit une structure Info_FIFO_Transaction
    do {
        read_res = read(server_fifo_fd, &message, sizeof(message));

        if (read_res > 0) {

            tmp_char_ptr = message.transaction;
            while (*tmp_char_ptr) {
                *tmp_char_ptr = toupper(*tmp_char_ptr);
                tmp_char_ptr++;
            }
            //Création du nom de FIFO client
            sprintf(client_fifo, CLIENT_FIFO_NAME, message.pid_client);

            //Après la lecture d’une structure Info_FIFO_Transaction provenant d’un client,
            //le serveur démarre un thread qui traite chaque transaction provenant des clients


            client_fifo_fd = open(client_fifo, O_WRONLY);
            if (client_fifo_fd != -1) {
                write(client_fifo_fd, &message, sizeof(message));
                close(client_fifo_fd);
            }

        }

    } while (read_res > 0);


    //Fin du programme
    exit(0);
}

