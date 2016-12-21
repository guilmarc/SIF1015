//#####################################################################
//#                                                                   #
//# Titre : 	server.c TP3 LINUX Automne 2016                       #
//#			SIF-1015 - Systeme d'exploitation	      				  #	
//#			Universite du Quebec a Trois-Rivieres         			  #
//#                                                                   #
//# Auteur : 	Adam Lemire & Remi Petiteau                           #
//# Date :	18 decembre 2016                                      	  #
//#                                                                   #
//# Langage : 	ANSI C on LINUX                                       #
//#                                                                   #
//#####################################################################

#include "gestionListeChaineeLinkedINFO.h"

//Pointeur de tete de liste
struct noeud* head;
//Pointeur de queue de liste pour ajout rapide
struct noeud* queue;

//Semaphore de tete et queue
sem_t sem_list;



void* traiter(void* arg){
	struct_transac data;
	int* sockfd = (int*) arg;
	char* tok;

	do{
		read(*sockfd,&data, sizeof(data));
		readTransLinkedINFO(data);
		tok = strtok(data.transaction, " ");
	}while(strcmp(tok,"E"));

	close(*sockfd);
	pthread_exit(0);
}

void start_pthread(){

	pthread_t client_th;

	//Creation d'un attribut pour les thread detach
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

	

	//Boucle sans fin en attente de clients
	while(1) {
		struct sockaddr_un client_adress;
		int client_sockfd;
		socklen_t client_len;
		client_len = sizeof(client_adress);
		client_sockfd = accept(server_socket_transac, (struct sockaddr *)&client_adress, &client_len);
		if( client_sockfd == -1 ) 
		  fprintf(stderr, "Client refuse pour la transaction\n");

		//Démarage du thread
		pthread_create(&client_th, &attr, traiter, &client_sockfd);
	}
}

int main(void)
{	
    int server_len;
    struct sockaddr_un server_adress_transac;
    struct sockaddr_un server_adress_comm;

  //Initialisation des pointeurs
  head = NULL;
  queue = NULL;

  //Initialisation du semaphore de tete et queue
  sem_init(&sem_list,0,1);
  //Initialisation des semaphores des threads
  sem_init(&sem_ajout, 0, 1);
  sem_init(&sem_modif, 0, 1);
  sem_init(&sem_elim, 0, 1);
  sem_init(&sem_affiche, 0, 1);
  sem_init(&sem_transmit, 0, 1);


  //Suppression de la socket existante
  unlink(SERVER_NAME_TRANSACTION);
  unlink(SERVER_NAME_COMMUNICATION);

  //Création des deux sockets
  server_socket_transac = socket(AF_UNIX, SOCK_STREAM,0);
  server_socket_comm = socket(AF_UNIX, SOCK_STREAM,0);

  //Identification de la socket de transaction
  server_adress_transac.sun_family = AF_UNIX;
  strcpy(server_adress_transac.sun_path, SERVER_NAME_TRANSACTION);
  server_len = sizeof(server_adress_transac);
  bind(server_socket_transac, (struct sockaddr *)&server_adress_transac, server_len);

  //identification de la socket de communication
  server_adress_comm.sun_family = AF_UNIX;
  strcpy(server_adress_comm.sun_path, SERVER_NAME_COMMUNICATION);
  server_len = sizeof(server_adress_comm);
  bind(server_socket_comm, (struct sockaddr *)&server_adress_comm, server_len);

  //Ecoute sur les deux sockets
  listen(server_socket_comm, NB_CLIENT);
  listen(server_socket_transac, NB_CLIENT);

  //Lance les threads
  start_pthread();

  //Fermeture du serveur
  close(server_socket_transac);
  close(server_socket_comm);
  unlink(SERVER_NAME_TRANSACTION);
  unlink(SERVER_NAME_COMMUNICATION); 
  printf("Fermeture du serveur\n");
    
  //Destruction du semaphore de queue et tete
  sem_destroy(&sem_list);
  //Destruction des semaphores des threads
  sem_destroy(&sem_ajout);
  sem_destroy(&sem_modif);
  sem_destroy(&sem_elim);
  sem_destroy(&sem_affiche);
  sem_destroy(&sem_transmit);
    
  exit(EXIT_SUCCESS);
}

