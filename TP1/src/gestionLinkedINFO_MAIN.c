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


int main(int argc, char* argv[]){
	//Initialisation des pointeurs
	head = NULL;
	queue = NULL;
	readTranslinkedINFO(argv[1]);
	//Fin du programme
	exit(0);
}
