//#########################################################
//#
//# Titre : 	Utilitaires Liste Chainee et CHAT LINUX Automne 16
//#			SIF-1015 - Systeme d'exploitation
//#			Universite du Quebec a Trois-Rivieres
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
//# Recherche le PREDECESSEUR d'un item dans la liste chainee
//#
//# RETOUR: Le pointeur vers le predecesseur est retourne
//# 		
//#			
//# 		Retourne NULL dans le cas ou l'item est introuvable
//#
struct noeud * findPrevlinkedINFO(const char* ptrNick){

	//La liste est vide 
	if ((head==NULL)&&(queue==NULL)) return NULL;

	//Pointeur de navigation
	struct noeud * ptr = head;

	//Tant qu'un item suivant existe
	while (ptr->suivant!=NULL){
	  
	  printf("\n dans findPrevlinkedINFO  nick suivant %s NICK %s COMPARAISON %d %d", ptr->suivant->membre.ptrNick,ptrNick, (int)(strlen(ptr->suivant->membre.ptrNick)), (int)(strlen(ptrNick)));

		//Est-ce le predecesseur de l'item recherche?
		if((strcmp(ptr->suivant->membre.ptrNick,ptrNick) == 0) ){
		
			//On retourne un pointeur sur l'item precedent
			return ptr;
		}

		//Deplacement du pointeur de navigation
		ptr=ptr->suivant;
		}

	//On retourne un pointeur NULL
	return NULL;
	}

//#######################################
//#
//# Ajoute un item dans la liste chainee
//#
void addItemlinkedINFO(const char* ptrNick, const char* ptrSpecialite, const char* ptrFormation, const int Experience){

	//Creation de l'enregistrement en memoire
	struct noeud* ni = (struct noeud*)malloc(sizeof(struct noeud));


	//Affectation des valeurs des champs
	strcpy(ni->membre.ptrNick, ptrNick);
	strcpy(ni->membre.ptrSpecialite, ptrSpecialite);
	strcpy(ni->membre.ptrFormation, ptrFormation);
	ni->membre.Experience = Experience;
	

	if(head == NULL) // ajout au debut de la liste vide
	{
		//  premier noeud 
		ni->suivant= NULL;
		queue = head = ni;

	}
	else  // ajout a la fin de la liste
	{
		struct noeud* tptr = queue;
		ni->suivant= NULL;
		queue = ni;
		tptr->suivant = ni;
	}
	
}

//#######################################
//#
//# Modifie un item de la liste chainee
//#
void modifyItemlinkedINFO(const int noNoeud, const char* ptrNick, const char* ptrSpecialite, const char* ptrFormation, const int Experience){

	int noentree=1;
	//Verification sommaire (noNickGroupe>0 et liste non vide)

	if ((noNoeud<1)||((head==NULL)&&(queue==NULL)))
		return;


	//Recherche de l'element a� modifier
	

	struct noeud * ptr = head;			//premier element


	while (ptr!=NULL){

		//Element a modifier
		if (noentree==noNoeud){
			//Affectation des valeurs des champs
			strcpy(ptr->membre.ptrNick, ptrNick);
			strcpy(ptr->membre.ptrSpecialite, ptrSpecialite);
			strcpy(ptr->membre.ptrFormation, ptrFormation);
			ptr->membre.Experience = Experience;
			//printf("%d: %s \t  %s \t %s \t %s \t %d\n",noentree,ptr->membre.ptrNick,ptr->membre.ptrFormation, ptr->membre.ptrSpecialite, ptr->membre.experience );
			return;
			}
		
		else{
			ptr = ptr->suivant;
			noentree++;
		}

	}

}


//#######################################
//#
//# Retire un item de la liste chainee
//#
void removeItemlinkedINFO(const char* ptrNick){
    struct noeud * ptr;
    struct noeud * optr;

    //Verification sommaire liste non vide
    
    if ((head==NULL)&&(queue==NULL)) 
      return;
    
    if(strcmp(head->membre.ptrNick,ptrNick) == 0)
    {
        ptr = head; // suppression du premier element de la liste

        if(head == ptr) // suppression de l'element de tete
        {
            if(head==queue) // un seul element dans la liste
            {
                free(ptr);
                queue = head = NULL;
                return;
            }
            head = ptr->suivant;
            //printf("tete\n");
            free(ptr);
        }
    }
    else
    {
        ptr = findPrevlinkedINFO(ptrNick); // ptr pointe sur l'element precedent de celui a supprimer

        //Item  trouve
        if (ptr!=NULL)
        {
            if (queue==ptr->suivant) // suppression de l'element de queue
            {
                queue=ptr;
                free(ptr->suivant);
                ptr->suivant=NULL;
                //printf("queue\n");
                return;
            }
            else // suppression d'un element dans la liste
            {
                optr = ptr->suivant;
                ptr->suivant = ptr->suivant->suivant;
                //printf("autre\n");
                free(optr);
            }
        }
    }
}


//#######################################
//#
//# Affiche les informations des membres dont le numero sequentiel est compris dans un intervalle
//#
void listItemsCompletlinkedINFO(const int start, const int end){

	int noentree=1;

	//Affichage des entetes de colonnes
	printf("\n======================================================\n");
	printf("NICK		Specialite       Formation       Experience                                          \n");
	printf("======================================================\n");

	struct noeud * ptr = head;			//premier element


	while (ptr!=NULL){

		//L'item a un numero sequentiel dans l'interval defini
		if ((noentree>=start)&&(noentree<=end)){
			printf("%d: %s \t\t  %s \t\t %s \t\t  %d\n",noentree,
				ptr->membre.ptrNick, ptr->membre.ptrSpecialite,
				ptr->membre.ptrFormation, ptr->membre.Experience);
			}
		if (noentree>end){
			//L'ensemble des items potentiels sont maintenant passes
			//Deplacement immediatement a� la FIN de la liste
			//Notez que le pointeur optr est toujours valide
			ptr=NULL;
			}
		else{
			ptr = ptr->suivant;
			noentree++;
		}

	}

	//Affichage des pieds de colonnes
	printf("======================================================\n\n");
}
//#######################################
//#
//# Affiche les informations des membres pour une specialite donnee
void listItemsParSpecialitelinkedINFO(const char* ptrSpecialite){
  
  
	int noentree=1;

	//Affichage des entetes de colonnes
	printf("\n======================================================\n");
	printf("NICK		Specialite       Formation       Experience                                          \n");
	printf("======================================================\n");

	struct noeud * ptr = head;			//premier element


	while (ptr!=NULL){

		//L'item a un numero sequentiel dans l'interval defini
		if ((strcmp(ptr->membre.ptrSpecialite,ptrSpecialite) == 0)){
			printf("%d: %s \t\t  %s \t\t %s \t\t  %d\n",noentree,
				ptr->membre.ptrNick, ptr->membre.ptrSpecialite,
				ptr->membre.ptrFormation, ptr->membre.Experience);
			}
		else{
			ptr = ptr->suivant;
			noentree++;
		}

	}

	//Affichage des pieds de colonnes
	printf("======================================================\n\n");
}

//#######################################
//#
//# Affiche les informations des membres pour une specialite et experience 
void listItemsParSpecialiteExperiencelinkedINFO(const char* ptrSpecialite, const int start, const int end){
  
	int noentree=1;


	//Affichage des entetes de colonnes
	printf("\n======================================================\n");
	printf("NICK		Specialite       Formation      Experience                                          \n");
	printf("======================================================\n");

	struct noeud * ptr = head;			//premier element


	while (ptr!=NULL){

		//L'item a un numero sequentiel dans l'interval defini
		if ((strcmp(ptr->membre.ptrSpecialite,ptrSpecialite) == 0) && ((ptr->membre.Experience >= start) && (ptr->membre.Experience <= end))){
			printf("%d: %s \t\t  %s \t\t %s \t\t  %d\n",noentree,
				ptr->membre.ptrNick, ptr->membre.ptrSpecialite,
				ptr->membre.ptrFormation, ptr->membre.Experience);
			}
		else{
			ptr = ptr->suivant;
			noentree++;
		}

	}

	//Affichage des pieds de colonnes
	printf("======================================================\n\n");
}

//#######################################
//#
//# Affiche les informations des membres pour une specialite et formation 
void listItemsParSpecialiteFormationlinkedINFO(const char* ptrSpecialite, const char* ptrFormation){
  
	int noentree=1;

	//Affichage des entetes de colonnes
	printf("\n======================================================\n");
	printf("NICK		Specialite       Formation       Experience                                          \n");
	printf("======================================================\n");

	struct noeud * ptr = head;			//premier element


	while (ptr!=NULL){

		//L'item a un numero sequentiel dans l'interval defini
		if ((strcmp(ptr->membre.ptrSpecialite,ptrSpecialite) == 0) && (strcmp(ptr->membre.ptrFormation,ptrFormation) == 0)){
			printf("%d: %s \t\t  %s \t\t %s \t\t  %d\n",noentree,
				ptr->membre.ptrNick, ptr->membre.ptrSpecialite,
				ptr->membre.ptrFormation, ptr->membre.Experience);
			}
		else{
			ptr = ptr->suivant;
			noentree++;
		}

	}

	//Affichage des pieds de colonnes
	printf("======================================================\n\n");
}

//#######################################
//#
//# Affiche les informations des membres pour une specialite formation et experience
void listItemsParSpecialiteFormationExperiencelinkedINFO(const char* ptrSpecialite, const char* ptrFormation, const int start, const int end ){

	int noentree=1;

	//Affichage des entetes de colonnes
	printf("\n======================================================\n");
	printf("NICK		Specialite       Formation       Experience                                          \n");
	printf("======================================================\n");

	struct noeud * ptr = head;			//premier element


	while (ptr!=NULL){

		//L'item a un numero sequentiel dans l'interval defini
		if ((strcmp(ptr->membre.ptrSpecialite,ptrSpecialite) == 0) && (strcmp(ptr->membre.ptrFormation,ptrFormation) == 0) && ((ptr->membre.Experience >= start) && (ptr->membre.Experience <= end))){
			printf("%d: %s \t\t  %s \t\t %s \t\t  %d\n",noentree,
				ptr->membre.ptrNick, ptr->membre.ptrSpecialite,
				ptr->membre.ptrFormation, ptr->membre.Experience);
			}
		else{
			ptr = ptr->suivant;
			noentree++;
		}

	}

	//Affichage des pieds de colonnes
	printf("======================================================\n\n");
}

//#######################################
//#
//# Transmission d'un message aux membres d'un groupe 
//#
void transTextGroupelinkedINFO(const char* ptrNick, const char* ptrGroupe, const char* ptrTexte){


	struct noeud * ptr = head;			//premier element


	printf("%s \t %s ",ptrNick, ptrGroupe);
	printf("TEXTE ENVOYE: %s\n",ptrTexte);

	while (ptr!=NULL){
		
		if((strcmp(ptr->membre.ptrNick,ptrNick) != 0) && ((strcmp(ptr->membre.ptrSpecialite,ptrGroupe) == 0) || (strcmp(ptr->membre.ptrFormation,ptrGroupe) == 0)))
		{						
				printf("membre: %s \t transmet au groupe: %s",ptr->membre.ptrNick, ptr->membre.ptrSpecialite);
				printf("   TEXTE ENVOYE/RECU: %s\n",ptrTexte);
		}
		ptr = ptr->suivant;

	}

}

//#######################################
//#
//# Transmission d'un message personnel a un membre 
//#
void transTextPersonnellinkedINFO(const char* ptrNick1, const char* ptrNick2, const char* ptrTexte){


	struct noeud * ptr = head;			//premier element


	printf("%s \t %s ",ptrNick1, ptrNick2);
	printf("TEXTE ENVOYE: %s\n",ptrTexte);

	while (ptr!=NULL){
		
		if((strcmp(ptr->membre.ptrNick,ptrNick1) != 0) && (strcmp(ptr->membre.ptrNick,ptrNick2) == 0))
		{						
				printf(" membre: %s \t transmet au membre: %s ",ptrNick1, ptrNick2);
				printf("TEXTE ENVOYE/RECU: %s\n",ptrTexte);
		}
		ptr = ptr->suivant;

	}

}
