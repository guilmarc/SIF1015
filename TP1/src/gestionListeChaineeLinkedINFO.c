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
extern Node* head;
//Pointeur de queue de liste pour ajout rapide
extern Node* queue;


//#######################################
//#
//# Recherche le PREDECESSEUR d'un item dans la liste chainee
//#
//# RETOUR: Le pointeur vers le predecesseur est retourne
//#
//#
//# 		Retourne NULL dans le cas ou l'item est introuvable
//#
Node * findPrevlinkedINFO(const char* nickname){

    //La liste est vide
    if ((head == NULL) && (queue == NULL)) {
        return NULL;
    }

    //Pointeur de navigation
    Node * ptr = head;

    //Tant qu'un item next existe
    while (ptr->next != NULL){

        //Est-ce le predecesseur de l'item recherche?
        if((strcmp(ptr->next->member.nickname, nickname) == 0) ){

            //On retourne un pointeur sur l'item precedent
            return ptr;
        }

        //Deplacement du pointeur de navigation
        ptr = ptr->next;
    }

    //On retourne un pointeur NULL
    return NULL;
}

//#######################################
//#
//# Ajoute un item dans la liste chainee
//#
//
void* addItemlinkedINFO(void* data) {

    //Creation de l'enregistrement en memoire
    Node* ni = (Node*)malloc(sizeof(Node));

    Member *member;
    member = (Member *) data;

    ni->member = *member;

    if(head == NULL) // ajout au debut de la liste vide
    {
        //  premier noeud
        ni->next= NULL;
        queue = head = ni;

    }
    else  // ajout a la fin de la liste
    {
        Node* tptr = queue;
        ni->next= NULL;
        queue = ni;
        tptr->next = ni;
    }
    pthread_exit(0);
}
//#######################################
//#
//# Modifie un item de la liste chainee
//#
void modifyItemlinkedINFO(const int nodeId, const char* nickname, const char* speciality, const char* scholarships, const int Experience){

    int entryId=1;
    //Verification sommaire (groupIde>0 et liste non vide)

    if ((nodeId<1) || ((head==NULL) && (queue==NULL))) {
        return;
    }
    //Recherche de l'element a� modifier
    Node * ptr = head;			//premier element
    while (ptr != NULL){

        //Element a modifier
        if (entryId == nodeId){
            //Affectation des valeurs des champs
            strcpy(ptr->member.nickname, nickname);
            strcpy(ptr->member.speciality, speciality);
            strcpy(ptr->member.scholarships, scholarships);
            ptr->member.experience = Experience;
            //printf("%d: %s \t  %s \t %s \t %s \t %d\n",entryId,ptr->membre.nickname,ptr->membre.scholarships, ptr->membre.speciality, ptr->membre.experience );
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
void removeItemlinkedINFO(const char* nickname){
    Node * ptr;
    Node * optr;

    //Verification sommaire liste non vide

    if ((head == NULL) && (queue == NULL)) {
        return;
    }

    if(strcmp(head->member.nickname,nickname) == 0)
    {
        ptr = head; // suppression du premier element de la liste

        if(head == ptr) // suppression de l'element de tete
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
        ptr = findPrevlinkedINFO(nickname); // ptr pointe sur l'element precedent de celui a supprimer

        //Item  trouve
        if (ptr != NULL)
        {
            if (queue == ptr->next) // suppression de l'element de queue
            {
                queue = ptr;
                free(ptr->next);
                ptr->next = NULL;
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
    }
}


//#######################################
//#
//# Affiche les informations des membres dont le numero sequentiel est compris dans un intervalle
//#
void listItemsCompletlinkedINFO(const int start, const int end){

    int entryId=1;
    printHeader();

    Node * ptr = head;			//premier element


    while (ptr != NULL){

        //L'item a un numero sequentiel dans l'interval defini
        if ((entryId >= start) && (entryId <= end)){
            printf("%d: %s \t\t  %s \t\t %s \t\t  %d\n",
                entryId,
                ptr->member.nickname, ptr->member.speciality,
                ptr->member.scholarships, ptr->member.experience
            );
        }
        if (entryId > end){
            //L'ensemble des items potentiels sont maintenant passes
            //Deplacement immediatement a� la FIN de la liste
            //Notez que le pointeur optr est toujours valide
            ptr = NULL;
        }
        else{
            ptr = ptr->next;
            entryId++;
        }

    }
    printFooter();
}
//#######################################
//#
//# Affiche les informations des membres pour une specialite donnee
void listItemsParSpecialitelinkedINFO(const char* speciality){


    int entryId = 1;
    printHeader();

    Node * ptr = head;			//premier element

    while (ptr != NULL){

        //L'item a un numero sequentiel dans l'interval defini
        if ((strcmp(ptr->member.speciality, speciality) == 0)){
            printf("%d: %s \t\t  %s \t\t %s \t\t  %d\n",
                entryId,
                ptr->member.nickname, ptr->member.speciality,
                ptr->member.scholarships, ptr->member.experience
            );
        }

        ptr = ptr->next;
        entryId++;
    }
    printFooter();
}

//#######################################
//#
//# Affiche les informations des membres pour une specialite et experience
void listItemsParSpecialiteExperiencelinkedINFO(const char* speciality, const int start, const int end){

    int entryId = 1;
    printHeader();
    Node * ptr = head;			//premier element

    while (ptr != NULL){

        //L'item a un numero sequentiel dans l'interval defini
        if ((strcmp(ptr->member.speciality, speciality) == 0) && ((ptr->member.experience >= start) && (ptr->member.experience <= end))){
            printf("%d: %s \t\t  %s \t\t %s \t\t  %d\n",
                entryId,
                ptr->member.nickname, ptr->member.speciality,
                ptr->member.scholarships, ptr->member.experience
            );
        }
        ptr = ptr->next;
        entryId++;

    }
    printFooter();
}

//#######################################
//#
//# Affiche les informations des membres pour une specialite et formation
void listItemsParSpecialiteFormationlinkedINFO(const char* speciality, const char* scholarships){

    int entryId = 1;
    printHeader();

    Node * ptr = head;			//premier element


    while (ptr != NULL){

        //L'item a un numero sequentiel dans l'interval defini
        if ((strcmp(ptr->member.speciality,speciality) == 0) && (strcmp(ptr->member.scholarships,scholarships) == 0)){
            printf("%d: %s \t\t  %s \t\t %s \t\t  %d\n",
                entryId,
                ptr->member.nickname, ptr->member.speciality,
                ptr->member.scholarships, ptr->member.experience
            );
        }

        ptr = ptr->next;
        entryId++;


    }
    printFooter();
}

//#######################################
//#
//# Affiche les informations des membres pour une specialite formation et experience
void listItemsParSpecialiteFormationExperiencelinkedINFO(const char* speciality, const char* scholarships, const int start, const int end ){

    int entryId = 1;
    printHeader();
    Node * ptr = head;			//premier element


    while (ptr != NULL){

        //L'item a un numero sequentiel dans l'interval defini
        if ((strcmp(ptr->member.speciality, speciality) == 0) && (strcmp(ptr->member.scholarships, scholarships) == 0) && ((ptr->member.experience >= start) && (ptr->member.experience <= end))){
            printf("%d: %s \t\t  %s \t\t %s \t\t  %d\n",
                entryId,
                ptr->member.nickname, ptr->member.speciality,
                ptr->member.scholarships, ptr->member.experience
            );
        }

        ptr = ptr->next;
        entryId++;


    }
    printFooter();
}

//#######################################
//#
//# Transmission d'un message aux membres d'un groupe
//#
void transTextGroupelinkedINFO(const char* nickname, const char* group, const char* text){

    Node * ptr = head;			//premier element

    printf("%s \t %s ",nickname, group);
    printf("TEXTE ENVOYE: %s\n", text);

    while (ptr != NULL){
        if((strcmp(ptr->member.nickname, nickname) != 0) && ((strcmp(ptr->member.speciality, group) == 0) || (strcmp(ptr->member.scholarships, group) == 0)))
        {
            printf("membre: %s \t transmet au groupe: %s",ptr->member.nickname, ptr->member.speciality);
            printf("   TEXTE ENVOYE/RECU: %s\n", text);
        }
        ptr = ptr->next;
    }
}

//#######################################
//#
//# Transmission d'un message personnel a un membre
//#
void transTextPersonnellinkedINFO(const char* nickname1, const char* nickname2, const char* text){

    Node * ptr = head;			//premier element

    printf("%s \t %s ", nickname1, nickname2);
    printf("TEXTE ENVOYE: %s\n", text);

    while (ptr != NULL){
        if((strcmp(ptr->member.nickname, nickname1) != 0) && (strcmp(ptr->member.nickname, nickname2) == 0))
        {
            printf(" membre: %s \t transmet au membre: %s ", nickname1, nickname2);
            printf("TEXTE ENVOYE/RECU: %s\n", text);
        }
        ptr = ptr->next;
    }
}

void printHeader() {
    //Affichage des entetes de colonnes
    printf("\n======================================================\n");
    printf("NICK		Specialite       Formation       Experience                                          \n");
    printf("======================================================\n");
}

void printFooter() {
    //Affichage des pieds de colonnes
    printf("======================================================\n\n");
}
