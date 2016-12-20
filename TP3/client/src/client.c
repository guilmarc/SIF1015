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
#include <sys/stat.h>


char* getFileName() {
    char *line = NULL;
    size_t len = 0;
    ssize_t read = 0;

    puts("Entrez le nom du fichier : ");
    read = getline(&line, &len, stdin);
    return line;
}

int main()
{
    int sockfd;
    int len;
    struct sockaddr_in address;
    int result;

    //char* filename = getFileName();
    //char* filename = "data.txt";
    char filename[50] = "data.txt";

    //Créer un socket pour le client
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    //Nommer le socket tel que demandé par le serveur
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = 9994;
    len = sizeof(address);

    //Connexion du socket local au socket du serveur déjà en mémoire
    result = connect(sockfd, (struct sockaddr *)&address, len);

    if( result == -1 ){
        perror("Erreur lors de la connexion au socket du serveur");
    }

    //Il est maintenant possible d'écrire et de lire via sockfd

    struct stat filestat;   //Structure contenant les infos d'un fichier

    write(sockfd, &filename, sizeof(filename));
    read(sockfd, &filestat, sizeof(filestat));
    printf("Donnée reçues du serveur = %d\n", filestat.st_size);
    close(sockfd);
    exit(0);
}

