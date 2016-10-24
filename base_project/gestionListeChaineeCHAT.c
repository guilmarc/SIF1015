//#########################################################
//#
//# Titre : 	Utilitaires Liste Chainee et CHAT LINUX Automne 13
//#			SIF-1015 - Systeme d'exploitation
//#			Universite du Quebec a Trois-Rivieres
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
//# Recherche le PREDECESSEUR d'un item dans la liste chainee
//#
//# RETOUR: Le pointeur vers le predecesseur est retourne
//#
//#
//# 		Retourne NULL dans le cas ou l'item est introuvable
//#
struct noeud * findPrevCHAT(const char* nickname, const char* group){

    //La liste est vide
    if ((head == NULL) && (queue == NULL)) {
        return NULL;
    }

    //Pointeur de navigation
    struct noeud * ptr = head;

    //Tant qu'un item next existe
    while (ptr->next != NULL){

        //Est-ce le predecesseur de l'item recherche?
        if((strcmp(ptr->next->membre.nickname, nickname)  ==  0) && (strcmp(ptr->next->membre.group, group)  ==  0)) {
            //On retourne un pointeur sur l'item precedent
            return ptr;
        }

        //Deplacement du pointeur de navigation
        ptr=ptr->next;
    }

    //On retourne un pointeur NULL
    return NULL;
}

//#######################################
//#
//# Ajoute un item dans la liste chainee
//#
void addItemCHAT(const char* nickname, const char* group){

    //Creation de l'enregistrement en memoire
    struct noeud* ni = (struct noeud*)malloc(sizeof(struct noeud));


    //Affectation des valeurs des champs
    strcpy(ni->membre.nickname, nickname);
    strcpy(ni->membre.group, group);


    if(head  ==  NULL) // ajout au debut de la liste vide
    {
        //  premier noeud
        ni->next= NULL;
        queue = head = ni;

    }
    else  // ajout a la fin de la liste
    {
        struct noeud* tptr = queue;
        ni->next= NULL;
        queue = ni;
        tptr->next = ni;
    }

}

//#######################################
//#
//# Modifie un item de la liste chainee
//#
void modifyItemCHAT(const int groupIde, const char* nickname, const char* group){

    int entryId = 1;
    //Verification sommaire (groupIde>0 et liste non vide)

    if ((groupIde < 1) || ((head == NULL) && (queue == NULL))) {
        return;
    }

    //Recherche de l'element a� modifier

    struct noeud * ptr = head;			//premier element


    while (ptr != NULL){

        //Element a modifier
        if (entryId == groupIde){
            //Affectation des valeurs des champs
            strcpy(ptr->membre.nickname, nickname);
            strcpy(ptr->membre.group, group);
            //printf("%d: %s \t\t  %s\n",entryId,ptr->membre.nickname,ptr->membre.group);
            return;
        }

        else{
            ptr = ptr->next;
            entryId++;
        }

    }

}


//#######################################
//#
//# Retire un item de la liste chainee
//#
void removeItemCHAT(const char* nickname, const char* group){

    struct noeud * ptr;
    struct noeud * optr;

    //Verification sommaire liste non vide

    if ((head == NULL)&&(queue == NULL))
    return;


    ​if((strcmp(head->membre.nickname,nickname)  ==  0) && (strcmp(head->membre.group,group)  ==  0) )
    {
        ptr = head; // suppression du premier element de la liste

        if(head  ==  ptr) // suppression de l'element de tete
        {
            if(head == queue) // un seul element dans la liste
            {
                free(ptr);
                queue = head = NULL;
                return;
            }
            head = ptr->next;
            //printf("tete\n");
            free(ptr);
        }
    }
    else
    {
        ptr = findPrevCHAT(nickname, group);

        //Item  trouve
        if (ptr != NULL)
        {
            if (queue == ptr->next) // suppression de l'element de queue
            {
                queue=ptr;
                free(ptr->next);
                ptr->next=NULL;
                //printf("queue\n");
                return;
            }
            else // suppression d'un element dans la liste
            {
                optr = ptr->next;
                ptr->next = ptr->next->next;
                //printf("autre\n");
                free(optr);
            }
        }
    }​
}


//#######################################
//#
//# Affiche les items dont le numero sequentiel est compris dans un intervalle
//#
void listItemsCHAT(const int start, const int end){

    int entryId = 1;

    //Affichage des entetes de colonnes
    printf("\n ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  == \n");
    printf("NICK		GROUPE                                          \n");
    printf(" ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  == \n");

    struct noeud * ptr = head;			//premier element

    while (ptr != NULL){
        //L'item a un numero sequentiel dans l'interval defini
        if ((entryId >= start) && (entryId <= end)){
            printf("%d: %s \t\t  %s\n",entryId,
            ptr->membre.nickname,
            ptr->membre.group);
        }
        if (entryId > end){
            //L'ensemble des items potentiels sont maintenant passes
            //Deplacement immediatement a� la FIN de la liste
            //Notez que le pointeur optr est toujours valide
            ptr=NULL;
        }
        else{
            ptr = ptr->next;
            entryId++;
        }
    }
    //Affichage des pieds de colonnes
    printf(" ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  == \n\n");
}

//#######################################
//#
//# Transmission d'un message aux membres d'un groupe
//#
void transTextCHAT(const char* nickname, const char* group, const char* text){
    struct noeud * ptr = head;			//premier element

    printf("%s \t %s ", nickname, group);
    printf("TEXTE ENVOYE: %s\n", text);

    while (ptr != NULL){

        if((strcmp(ptr->membre.nickname, nickname)  !=  0) && (strcmp(ptr->membre.group, group)  ==  0) ) {
            printf("%s \t %s ", ptr->membre.nickname, ptr->membre.group);
            printf("TEXTE RECU: %s\n",text);
        }
        ptr = ptr->next;
    }
}
