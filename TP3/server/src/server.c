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

int main()
{

    //Ce code fonctionne pour la lecture des stats de fichier
    struct stat filestat;
    stat("data.txt", &filestat);

    //TEST D'UTILISATION DE STAT

    int server_sockfd, client_sockfd;
    int server_len, client_len;
    struct sockaddr_un server_address;
    struct sockaddr_un client_address;

    //Supprimer le socket existant et en créer un sans nom
    unlink("server_socket");
    server_sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

    //Nommer le socket
    server_address.sun_family = AF_UNIX;
    strcpy(server_address.sun_path, "server_socket");
    server_len = sizeof(server_address);
    bind(server_sockfd, (struct sockaddr *)&server_address, server_len);

    //Création d'une file de connexions et attente des clients
    listen(server_sockfd, 5);
    while(1) {
        char ch;

        printf("Serveur actif en attente de connexions...");

        //Accepter une connexion
        client_len = sizeof(client_address);
        client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_address, &client_len);

        //On peut maintenant lire et écrire au client en utilisant le client_sockfd
        read(client_sockfd, &ch, 1);
        ch++;
        write(client_sockfd, &ch, 1);
        close(client_sockfd);

    }

}