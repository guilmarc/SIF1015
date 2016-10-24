//#########################################################
//#
//# Titre : 	Utilitaires CHAT LINUX Automne 13
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
extern struct noeud* head;
//Pointeur de queue de liste pour ajout rapide
extern struct noeud* queue;

//#######################################
//#
//# Affiche un message et quitte le programme
//#
void error(const int exitcode, const char * message){
	printf("\n-------------------------\n%s\n",message);
	exit(exitcode);
	}




//#######################################
//#
//# fonction utilisee par les threads de transactions
//#
void* readTransCHAT(char* nomFichier){
	FILE *f;
	char buffer[100];
	char *tok, *sp;

	//Ouverture du fichier en mode "r" (equiv. "rt") : [r]ead [t]ext
	f = fopen(nomFichier, "rt");
	if (f==NULL)
		error(2, "readTrans: Erreur lors de l'ouverture du fichier.");

	//Lecture (tentative) d'une ligne de texte
	fgets(buffer, 100, f);

	//Pour chacune des lignes lues
	while(!feof(f)){

		//Extraction du type de transaction
		tok = strtok_r(buffer, " ", &sp);

		//Branchement selon le type de transaction
		switch(tok[0]){
			case 'A':
			case 'a':{
				//Extraction des parametres
				char *nickname = strtok_r(NULL, " ", &sp);
				char *group = strtok_r(NULL, "\n", &sp);
				//Appel de la fonction associee
				addItemCHAT(nickname, group);
				break;
				}
			case 'M':
			case 'm':{
				//Extraction des parametres
				int groupIde = atoi(strtok_r(NULL, " ", &sp));
				char *nickname = strtok_r(NULL, " ", &sp);
				char *group = strtok_r(NULL, "\n", &sp);
				//Appel de la fonction associee
				modifyItemCHAT(groupIde,nickname, group);
				break;
				}
			case 'E':
			case 'e':{
				//Extraction du parametre
				char *nickname = strtok_r(NULL, " ", &sp);
				char *group = strtok_r(NULL, "\n", &sp);

				//Appel de la fonction associee
				removeItemCHAT(nickname, group);
				break;
				}
			case 'L':
			case 'l':{
				//Extraction des parametres
				int nstart = atoi(strtok_r(NULL, "-", &sp));
				int nend = atoi(strtok_r(NULL, " ", &sp));
				//Appel de la fonction associee
				listItemsCHAT(nstart, nend);
				break;
				}
			case 'T':
			case 't':{
				//Extraction des parametres
				char *nickname = strtok_r(NULL, " ", &sp);
				char *group = strtok_r(NULL, " ", &sp);
				char *text = strtok_r(NULL, "\n", &sp);

				//Appel de la fonction associee
				transTextCHAT(nickname, group,text);
				break;
				}

		}

		//Lecture (tentative) de la prochaine ligne de texte
		fgets(buffer, 100, f);
	}
	//Fermeture du fichier
	fclose(f);
	//Retour
	return NULL;
}


