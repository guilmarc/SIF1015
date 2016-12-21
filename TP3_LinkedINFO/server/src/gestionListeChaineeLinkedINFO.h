//#####################################################################
//#                                                                   #
//# Titre : gestionListeChaineeLinkedINFO.h TP3 LINUX Automne 2016    #
//#			SIF-1015 - Systeme d'exploitation                         # 
//#			Universite du Quebec a Trois-Rivieres                     #
//#                                                                   #
//# Auteur : 	Adam Lemire & Remi Petiteau                           #
//#	Date :	18 decembre 2016                                           #
//#                                                                   #
//# Langage : 	ANSI C on LINUX                                       #
//#                                                                   #
//#####################################################################

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/un.h>
#include <sys/socket.h>

#include <fcntl.h>
#include <limits.h>
#include <sys/stat.h>
#include <ctype.h>

#include <errno.h>

#define NB_CLIENT 10

//Definition des chemin
//#define SERVER_FIFO_NAME "./FIFO_TRANSACTIONS"
//#define FIFO_TRANSACTIONS "./FIFO_TRANSACTIONS"
//#define CLIENT_FIFO_NAME "./FIFO%d"
#define SERVER_NAME_TRANSACTION "serveur transaction"
#define SERVER_NAME_COMMUNICATION "serveur communication"

#define BUFFER_SIZE 20
#define ls ACS_VLINE
#define bs ACS_HLINE
#define nb_ligne 70
#define nb_colonne 50
#define size 200

//Structure FIFO
struct Info_Transaction{
	int pid_client;
	char transaction[400];
};

typedef struct Info_Transaction struct_transac;

int server_socket_transac;
int server_socket_comm;
//int server_fifo_fd;

//Semaphore de queue et head
extern sem_t sem_list;

//Semaphore des threads
sem_t sem_ajout;
sem_t sem_modif;
sem_t sem_elim;
sem_t sem_affiche;
sem_t sem_transmit;

/** Structure des donnees **/

struct infoMembre{
  int client_fd;
  int pid;
  char ptrNick[100];
  char ptrSpecialite[100];
  char ptrFormation[100];
  int experience;
};

struct noeud{
	struct infoMembre membre;
	struct noeud *suivant;
};

typedef struct{
  char *ptrNick;
  char *ptrSpecialite;
  char *ptrFormation;
  int experience;
  int socket;
  int pid; 
}struct_ajout, *p_struct_ajout;

typedef struct{
  char *ptrNick;
  char *ptrSpecialite;
  char *ptrFormation;
  int experience;
}struct_elim, *p_struct_elim;

typedef struct{
  int pid;
  int nstart;
  int nend;
}struct_afficheC, *p_struct_afficheC;

typedef struct {
  char *ptrSpecialite;
  int pid;
  }infoLISTS, *p_struct_afficheS;
	
typedef struct {							
  char *ptrSpecialite;
  int nstart;
  int nend;
  int pid;
  }infoLISTSE, *p_struct_afficheSE;
	
typedef struct {					
  char *ptrSpecialite;
  char *ptrFormation;
  int pid;
  }infoLISTSF, *p_struct_afficheSF;

typedef struct {	
  char *ptrSpecialite;
  char *ptrFormation;
  int nstart;
  int nend;
  int pid;
  }infoLISTSFE, *p_struct_afficheSFE;

typedef struct{
  char *ptrNick;
  char *ptrSpecialite;
  char *ptrTexte;
}struct_transmit, *p_struct_transmit;

typedef struct{
  char *ptrNick1;
  char *ptrNick2;
  char *ptrTexte;
}struct_transmitpp, *p_struct_transmitpp;

/** Definition des fonctions **/
void error(const int exitcode, const char * message);

void* readTransLinkedINFO(struct Info_Transaction my_data);

struct noeud * findPrevLinkedINFO(const char* ptrNick, const char* ptrSpecialite, const char* ptrFormation, const int experience);

void addItemLinkedINFO(const char* ptrNick, const char* ptrSpecialite, const char* ptrFormation, const int experience,const int socket,const int pid);
void removeItemLinkedINFO(const char* ptrNick, const char* ptrSpecialite, const char* ptrFormation, const int experience);
void listItemsC(const int start, const int end,const int pid);
void listItemsS(const char* ptrSpecialite,const int pid);
void listItemsSE(const char* ptrSpecialite, const int start, const int end, const int pid);
void listItemsSF(const char* ptrSpecialite, const char* ptrFormation, const int pid);
void listItemsSFE(const char* ptrSpecialite, const char* ptrFormation, const int start, const int end,const int pid);
void transTextPG(const char* ptrNick, const char* ptrSpecialite, const char* ptrTexte);
void transTextPP(const char* ptrNick1, const char* ptrNick2, const char* ptrTexte);


void* thread_ajout(void *arg);
void* thread_modif(void *arg);
void* thread_elim(void *arg);
void* thread_affiche(void *arg);
void* thread_afficheS(void *arg);
void* thread_afficheSE(void *arg);
void* thread_afficheSF(void *arg);
void* thread_afficheSFE(void *arg);
void* thread_transmit(void *arg);
void* thread_transmitpp(void *arg);

void send_transaction(char* msg);
void init_screen(void);
void screen_ID(void);
void screen_transmit(void);
void* transmit_msg(void* arg);
void* receiv_msg(void* arg);
void screen_reception(void);
void end_screen(void);
