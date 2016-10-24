//#########################################################
//#
//# Titre : 	Utilitaires CHAT LINUX Automne 16
//#			SIF-1015 - Systeme d'exploitation
//#			Universite du Quebec aï¿½ Trois-Rivieres
//#
//# Auteur : 	Francois Meunier
//#	Date :	Septembre 2016
//#
//# Langage : 	ANSI C on LINUX
//#
//#######################################

#include "gestionListeChaineeLinkedINFO.h"

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
void* readTranslinkedINFO(char* nomFichier){
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
				char *ptrNick = strtok_r(NULL, " ", &sp);
				char *ptrSpecialite = strtok_r(NULL, " ", &sp);
				char *ptrFormation = strtok_r(NULL, " ", &sp);
				int experience = atoi(strtok_r(NULL, "\n", &sp));
				//Appel de la fonction associee
				addItemlinkedINFO(ptrNick, ptrSpecialite, ptrFormation, experience);
				break;
			}
			case 'M':
			case 'm':{
				//Extraction des parametres
				int noNoeud = atoi(strtok_r(NULL, " ", &sp));
				char *ptrNick = strtok_r(NULL, " ", &sp);
				char *ptrSpecialite = strtok_r(NULL, " ", &sp);
				char *ptrFormation = strtok_r(NULL, " ", &sp);
				int experience = atoi(strtok_r(NULL, "\n", &sp));
				//Appel de la fonction associee
				modifyItemlinkedINFO(noNoeud, ptrNick, ptrSpecialite, ptrFormation, experience);
				break;
			}
			case 'E':
			case 'e':{
				//Extraction du parametre
				char *ptrNick = strtok_r(NULL, "\n", &sp);

				//Appel de la fonction associee
				removeItemlinkedINFO(ptrNick);
				break;
			}
			case 'L':
			case 'l':{
				//Extraction des parametres
				char *ptrType = strtok_r(NULL, " ", &sp);

				if(strcmp(ptrType, "C") == 0) // affichage complet
				{
					int nstart = atoi(strtok_r(NULL, "-", &sp));
					int nend = atoi(strtok_r(NULL, "\n", &sp));
					//Appel de la fonction associee
					listItemsCompletlinkedINFO(nstart, nend);
				}
				else if(strcmp(ptrType, "S") == 0) // affichage par specialite
				{
					char* ptrSpecialite = strtok_r(NULL, "\n", &sp);
					//Appel de la fonction associee
					listItemsParSpecialitelinkedINFO(ptrSpecialite);
				}
				else if(strcmp(ptrType, "SE") == 0) // affichage par specialite et experience
				{
					char* ptrSpecialite = strtok_r(NULL, " ", &sp);
					int nstart = atoi(strtok_r(NULL, "-", &sp));
					int nend = atoi(strtok_r(NULL, "\n", &sp));
					//Appel de la fonction associee
					listItemsParSpecialiteExperiencelinkedINFO(ptrSpecialite, nstart, nend);
				}
				else if(strcmp(ptrType, "SF") == 0) // affichage par specialite et formation
				{
					char* ptrSpecialite = strtok_r(NULL, " ", &sp);
					char* ptrFormation = strtok_r(NULL, "\n", &sp);
					//Appel de la fonction associee
					listItemsParSpecialiteFormationlinkedINFO(ptrSpecialite, ptrFormation);
				}
				else if(strcmp(ptrType, "SFE") == 0) // affichage par specialite formation et experience
				{
					char* ptrSpecialite = strtok_r(NULL, " ", &sp);
					char* ptrFormation = strtok_r(NULL, " ", &sp);
					int nstart = atoi(strtok_r(NULL, "-", &sp));
					int nend = atoi(strtok_r(NULL, "\n", &sp));
					//Appel de la fonction associee
					listItemsParSpecialiteFormationExperiencelinkedINFO(ptrSpecialite, ptrFormation, nstart, nend);
				}
				break;
			}
			case 'T':
			case 't':{

				//Extraction des parametres
				char *ptrType = strtok_r(NULL, " ", &sp);

				if(strcmp(ptrType, "PG") == 0) // affichage complet
				{
					char *ptrNick = strtok_r(NULL, " ", &sp);
					char *ptrGroupe = strtok_r(NULL, " ", &sp);
					char *ptrTexte = strtok_r(NULL, "\n", &sp);

					//Appel de la fonction associee
					transTextGroupelinkedINFO(ptrNick, ptrGroupe,ptrTexte);

				}
				else if(strcmp(ptrType, "PP") == 0) // affichage complet
				{
					char *ptrNick1 = strtok_r(NULL, " ", &sp);
					char *ptrNick2 = strtok_r(NULL, " ", &sp);
					char *ptrTexte = strtok_r(NULL, "\n", &sp);

					//Appel de la fonction associee
					transTextPersonnellinkedINFO(ptrNick1, ptrNick2,ptrTexte);

				}
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

