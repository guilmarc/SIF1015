//#########################################################
//#
//# Titre : 	UTILITAIRES (MAIN) TP1 LINUX Automne 13
//#			SIF-1015 - Systeme d'exploitation
//#			Universite du Quebec a� Trois-Rivieres
//#
//# Auteur : 	Francois Meunier
//#	Date :	Septembre 2013
//#
//# Langage : 	ANSI C on LINUX 
//#
//#######################################

#include "gestionListeChaineeCHAT.h"

//Pointeur de tete de liste
struct noeud* head;
//Pointeur de queue de liste pour ajout rapide
struct noeud* queue;


int main(int argc, char* argv[]){
	//Initialisation des pointeurs
	head = NULL;
	queue = NULL;
	readTransCHAT(argv[1]);
	//Fin du programme
	exit(0);
}

