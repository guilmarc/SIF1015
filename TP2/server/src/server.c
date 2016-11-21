//
// Created by Marco Guillemette on 2016-11-20.
//

#include "server.h"
#include "handleTransaction.h"
#include "../../client/src/client.h"

#include <ctype.h>
#include <pthread.h>


void* sendTransaction(void* data){
    int client_fifo_fd;

    SendTransactionParams* params = (SendTransactionParams*)data;

    client_fifo_fd = open(params->client_fifo, O_WRONLY);
    if (client_fifo_fd != -1) {
        write(client_fifo_fd, &params->data, sizeof(params->data));
        close(client_fifo_fd);
    }
}

int initTmpDirectory() {
    return mkdir("./tmp", 0777);
}

void startServer()
{
    int server_fifo_fd, client_fifo_fd;
    ssize_t read_res;
    Info_FIFO_Transaction transaction;
    char client_fifo[100];
    char *tmp_char_ptr;
<<<<<<< HEAD
    printf("%i", initTmpDirectory());

=======
    int mkfifo_return;
>>>>>>> 479ea159e9b2264b76b85b29e7b53f5bca3960db

    //La FIFO de transmission de transactions devra s’appeler FIFO_TRANSACTIONS.
    //Cette FIFO est créée par le programme serveur lors de son démarrage et est ouverte par le serveur en lecture (bloquante).
    mkfifo_return = mkfifo(SERVER_FIFO_NAME, 0777);
    printf("MKFifo Return = %i", mkfifo_return);

    server_fifo_fd = open(SERVER_FIFO_NAME, O_RDONLY);
    printf("server_fifo_fd = %i", server_fifo_fd);

    //Ensuite, le serveur boucle en lecture sur la FIFO FIFO_TRANSACTIONS pour lire les informations provenant des clients.
    //À chaque lecture, le serveur lit une structure Info_FIFO_Transaction
    //do {

    printf("Yo Buddy, je roule !!!");
    int i = 3;

    while( i > 1) {

        printf("read_res\n");
        read_res = read(server_fifo_fd, &transaction, sizeof(transaction));

        sleep(1);
        printf("OK : %d\n", read_res);

        if (read_res > 0) {

            tmp_char_ptr = transaction.transaction;
            while (*tmp_char_ptr) {
                *tmp_char_ptr = toupper(*tmp_char_ptr);
                tmp_char_ptr++;
            }
            //Création du nom de FIFO client
            sprintf(client_fifo, CLIENT_FIFO_NAME, transaction.pid_client);

            //Après la lecture d’une structure Info_FIFO_Transaction provenant d’un client,
            //le serveur démarre un thread qui traite chaque transaction provenant des clients

            void *result = parseTransaction(transaction.transaction, client_fifo);

            //Les threads du côté serveur qui traitent chaque requête des clients doivent alors ouvrir une FIFO en écriture
            //(bloquante) pour permettre de répondre à chaque client, cette FIFO étant créée au préalable par le client lors de son démarrage.
            //Cette FIFO a un  nom correspondant à la concaténation de la chaîne de caractères "FIFO" concaténée au pid du thread côté client


            //Les threads du côté serveur  doivent aussi répondre aux clients dans le cas d’une requête d’affichage (ex : L C 1-10)
            //ou les threads (côté serveur) déposent les structures infoMembre sérialisées chacune dans une chaîne de caractères (dimension 400)
            //déposées ensuite dans la FIFO (client_fifo)  reliant le serveur et un client particulier qui sont à afficher du côté client.


            //Création d'ue nouvelle struct
            SendTransactionParams *params = (SendTransactionParams *) malloc(sizeof(SendTransactionParams));
            params->client_fifo = client_fifo;
            params->data = result;

            pthread_t thread;
            pthread_create(&thread, NULL, sendTransaction, params);

        }
    } while (1);
    printf("Je roule pu !!!");
    //} while (read_res > 0);
}