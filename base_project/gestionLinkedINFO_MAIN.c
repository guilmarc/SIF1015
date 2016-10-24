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

Node* head;
Node* queue;

int main(int argc, char* argv[]) {
	head = NULL;
	queue = NULL;
	readTrans(argv[1]);
	exit(0);
}
