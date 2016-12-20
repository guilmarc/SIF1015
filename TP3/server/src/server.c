//
// Created by Marco Guillemette on 2016-12-19.
//

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <netinet/in.h>

#include <stdlib.h>

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define PORT = 9999
#define MAX_CONNECTIONS = 5

void runServer();

int main()
{

    //Ce code fonctionne pour la lecture des stats de fichier
    struct stat filestat;
    stat("data.txt", &filestat);

    runServer();

}


//void old() {
//    //TEST D'UTILISATION DE STAT
//
//    int server_sockfd, client_sockfd;
//    int server_len, client_len;
//    struct sockaddr_un server_address;
//    struct sockaddr_un client_address;
//
//    //Supprimer le socket existant et en créer un sans nom
//    unlink("server_socket");
//    server_sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
//
//    //Nommer le socket
//    server_address.sun_family = AF_UNIX;
//    strcpy(server_address.sun_path, "server_socket");
//    server_len = sizeof(server_address);
//    bind(server_sockfd, (struct sockaddr *)&server_address, server_len);
//
//    //Création d'une file de connexions et attente des clients
//    listen(server_sockfd, 5);
//    while(1) {
//        char ch;
//
//        printf("Serveur actif en attente de connexions...");
//
//        //Accepter une connexion
//        client_len = sizeof(client_address);
//        client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_address, &client_len);
//
//        //On peut maintenant lire et écrire au client en utilisant le client_sockfd
//        read(client_sockfd, &ch, 1);
//        ch++;
//        write(client_sockfd, &ch, 1);
//        close(client_sockfd);
//
//    }
//}

void runServer() {


    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == INVALID_SOCKET) {
        perror("Impossible de créer le socket");
        exit(-1);
    }

    struct sockaddr_in sin = {0};

    sin.sin_addr.s_addr = htonl(INADDR_ANY); /* nous sommes un serveur, nous acceptons n'importe quelle adresse */

    sin.sin_family = AF_INET;

    sin.sin_port = 9994; // htons(9999);

    if (bind(server_socket, (struct sockaddr *) &sin, sizeof sin) == SOCKET_ERROR) {
        perror("Impossible de lier le socket à l'adapteur réseau");
        exit(-1);
    }


    if (listen(server_socket, 5) == SOCKET_ERROR) {
        perror("Impossible d'écouter sur le port demandé");
        exit(-1);
    }

    while (1) {
        //La fonction accept renvoie un nouveau socket, il faut donc le stocker dans une nouvelle variable. Désormais, c'est ce socket que nous utiliserons pour communiquer avec notre client. Nous l'utiliserons pour faire des read ou des send.

        struct sockaddr_in csin = {0};
        int client_socket;

        int sinsize = sizeof csin;

        client_socket = accept(server_socket, (struct socketaddr *) &csin, &sinsize);

        if (client_socket == INVALID_SOCKET) {
            perror("Le serveur est incapable d'accepter la connexion");
            exit(-1);
        }

        char filename[50];
        read(client_socket, &filename, 50);

        printf("SERVEUR: Donnée reçue du client = %s\n", filename);

        struct stat filestat;
        stat(&filename, &filestat);

        write(client_socket, &filestat, sizeof(filestat));

        close(client_socket);

    }
}