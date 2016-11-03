//#########################################################
//#
//# Titre : 	UTILITAIRES (MAIN) TP1 LINUX Automne 16
//#			SIF-1015 - Systeme d'exploitation
//#			Universite du Quebec a� Trois-Rivieres
//#
//# Auteur : 	Francois Meunier
//#	Date :	Septembre 2016
//#
//# Langage : 	ANSI C on LINUX
//#
//#######################################

#include "gestionListeChaineeLinkedINFO.h"

//Pointeur de tete de liste
Node* head;
//Pointeur de queue de liste pour ajout rapide
Node* queue;

sem_t head_semaphore;
sem_t queue_semaphore;

//sem_t mutex;      /* semaphore that protects counter */

int main(int argc, char* argv[]){
    //Initialisation des pointeurs
    head = NULL;
    queue = NULL;

    //Initialisation des semaphores de tête, de queue et d'affichage
    sem_init(&head_semaphore, 0, 1);
    sem_init(&queue_semaphore, 0, 1);
    sem_init(&print_semaphore, 0, 1);

    readTransactionsFile(argv[1]);
    //Fin du programme
    exit(0);
}
