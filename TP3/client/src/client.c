//
// Created by Marco Guillemette on 2016-12-19.
//


#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>

int main()
{
    int sockfd;
    int len;
    struct sockaddr_in address;
    int result;
    char ch= 'A';

    //Créer un socket pour le client
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    //Nommer le socket tel que demandé par le serveur
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = 9734;
    len = sizeof(address);

    //Connexion du socket local au socket du serveur déjà en mémoire
    result = connect(sockfd, (struct sockaddr *)&address, len);

    if( result == -1 ){
        perror("Erreur lors de la connexion au socket du serveur");
    }

    //Il est maintenant possible d'écrire et de lire via sockfd
    write(sockfd, &ch, 1);
    read(sockfd, &ch, 1);
    printf("Donnée reçues du serveur = %c\n", ch);
    close(sockfd);
    exit(0);
}