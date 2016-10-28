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

sem_t mutex;      /* semaphore that protects counter */

//#######################################
//#
//# Recherche le PREDECESSEUR d'un item dans la liste chainee
//#
//# RETOUR: Le pointeur vers le predecesseur est retourne
//#
//#
//# 		Retourne NULL dans le cas ou l'item est introuvable
//#
Node * findPrevious(const char* nickname){

    //La liste est vide
    if ((head == NULL) && (queue == NULL)) {
        return NULL;
    }

    //Pointeur de navigation
    Node * ptr = head;

    //Tant qu'un item next existe
    while (ptr->next != NULL){
        sem_wait(&mutex);

        //Est-ce le predecesseur de l'item recherche?
        if((strcmp(ptr->next->member.nickname, nickname) == 0) ){

            //On retourne un pointeur sur l'item precedent
            return ptr;
        }

        //Deplacement du pointeur de navigation
        ptr = ptr->next;
        sem_post(&mutex);
    }

    //On retourne un pointeur NULL
    return NULL;
}

//#######################################
//#
//# Ajoute un item dans la liste chainee
//#
//
void* addItem(void* data) {

    //Creation de l'enregistrement en memoire
    Node* ni = (Node*)malloc(sizeof(Node));

    AddItemParams* params = (AddItemParams *) data;

    ni->member = params->member;

    if(head == NULL) // ajout au debut de la liste vide
    {

        sem_wait(&mutex);
        //  premier noeud
        ni->next= NULL;
        queue = head = ni;
        sem_post(&mutex);
    }
    else  // ajout a la fin de la liste
    {
        sem_wait(&mutex);
        Node* tptr = queue;
        ni->next= NULL;
        queue = ni;
        tptr->next = ni;
        sem_post(&mutex);
    }
    pthread_exit(0);
}
//#######################################
//#
//# Modifie un item de la liste chainee
//#
void* modifyItem(void* data){

    ModifyItemParams* params = (ModifyItemParams *) data;

    int entryId=1;
    //Verification sommaire (groupIde>0 et liste non vide)

    if ((params->nodeId<1) || ((head==NULL) && (queue==NULL))) {
        return NULL;
    }
    //Recherche de l'element a� modifier
    Node *ptr = head;			//premier element
    while (ptr != NULL){

        sem_wait(&mutex);
        //Element a modifier
        if (entryId == params->nodeId){
            //Affectation des valeurs des champs
            strcpy(ptr->member.nickname, params->member.nickname);
            strcpy(ptr->member.speciality, params->member.speciality);
            strcpy(ptr->member.scholarships, params->member.scholarships);
            ptr->member.experience = params->member.experience;
            //printf("%d: %s \t  %s \t %s \t %s \t %d\n",entryId,ptr->membre.nickname,ptr->membre.scholarships, ptr->membre.speciality, ptr->membre.experience );
            return NULL;
        }
        else{
            ptr = ptr->next;
            entryId++;
        }
        sem_post(&mutex);
    }
    return NULL;
}


//#######################################
//#
//# Retire un item de la liste chainee
//#
void* removeItem(void* data){
    Node * ptr;
    Node * optr;

    RemoveItemParams* params = (RemoveItemParams *) data;

    //Verification sommaire liste non vide

    if ((head == NULL) && (queue == NULL)) {
        return NULL;
    }

    if(strcmp(head->member.nickname,params->nickname) == 0)
    {
        ptr = head; // suppression du premier element de la liste

        if(head == ptr) // suppression de l'element de tete
        {
            sem_wait(&mutex);
            if(head == queue) // un seul element dans la liste
            {
                free(ptr);
                queue = head = NULL;
                return NULL;
            }
            head = ptr->next;
            //printf("tete\n");
            free(ptr);
            sem_post(&mutex);
        }
    }
    else
    {
        ptr = findPrevious(params->nickname); // ptr pointe sur l'element precedent de celui a supprimer

        //Item  trouve
        if (ptr != NULL)
        {
            if (queue == ptr->next) // suppression de l'element de queue
            {
                sem_wait(&mutex);
                queue = ptr;
                free(ptr->next);
                ptr->next = NULL;
                //printf("queue\n");
                sem_post(&mutex);
                return NULL;
            }
            else // suppression d'un element dans la liste
            {
                sem_wait(&mutex);
                optr = ptr->next;
                ptr->next = ptr->next->next;
                //printf("autre\n");
                free(optr);
                sem_post(&mutex);
            }
        }
    }
    return NULL;
}


//#######################################
//#
//# Affiche les informations des membres dont le numero sequentiel est compris dans un intervalle
//#
void* listItemsWithinInterval(void* data){

    int entryId=1;
    printHeader();

    Node * ptr = head;			//premier element

    ListItemsWithinIntervalParams* params = (ListItemsWithinIntervalParams *) data;

    while (ptr != NULL){

        sem_wait(&mutex);
        //L'item a un numero sequentiel dans l'interval defini
        if ((entryId >= params->start) && (entryId <= params->end)){
            printf("%d: %s \t\t  %s \t\t %s \t\t  %d\n",
                entryId,
                ptr->member.nickname, ptr->member.speciality,
                ptr->member.scholarships, ptr->member.experience
            );
        }
        if (entryId > params->end){
            //L'ensemble des items potentiels sont maintenant passes
            //Deplacement immediatement a� la FIN de la liste
            //Notez que le pointeur optr est toujours valide
            ptr = NULL;
        }
        else{
            ptr = ptr->next;
            entryId++;
        }
        sem_post(&mutex);

    }
    printFooter();
    return NULL;
}
//#######################################
//#
//# Affiche les informations des membres pour une specialite donnee
void* listItemsPerSpeciality(void* data){


    int entryId = 1;
    printHeader();

    Node * ptr = head;			//premier element

    ListItemsPerSpecialityParams* params = (ListItemsPerSpecialityParams *) data;

    while (ptr != NULL){
        sem_wait(&mutex);

        //L'item a un numero sequentiel dans l'interval defini
        if ((strcmp(ptr->member.speciality, params->speciality) == 0)){
            printf("%d: %s \t\t  %s \t\t %s \t\t  %d\n",
                entryId,
                ptr->member.nickname, ptr->member.speciality,
                ptr->member.scholarships, ptr->member.experience
            );
        }

        ptr = ptr->next;
        entryId++;
        sem_post(&mutex);
    }
    printFooter();
    return NULL;
}

//#######################################
//#
//# Affiche les informations des membres pour une specialite et experience
void* listItemsPerSpecialityAndExperienceInterval(void* data){

    int entryId = 1;
    printHeader();
    Node * ptr = head;			//premier element

    ListItemsPerSpecialityAndExperienceIntervalParams* params = (ListItemsPerSpecialityAndExperienceIntervalParams *) data;

    while (ptr != NULL){
        sem_wait(&mutex);

        //L'item a un numero sequentiel dans l'interval defini
        if ((strcmp(ptr->member.speciality, params->speciality) == 0) && ((ptr->member.experience >= params->start) && (ptr->member.experience <= params->end))){
            printf("%d: %s \t\t  %s \t\t %s \t\t  %d\n",
                entryId,
                ptr->member.nickname, ptr->member.speciality,
                ptr->member.scholarships, ptr->member.experience
            );
        }
        ptr = ptr->next;
        entryId++;

        sem_post(&mutex);
    }
    printFooter();
    return NULL;
}

//#######################################
//#
//# Affiche les informations des membres pour une specialite et formation
void* listItemsPerSpecialityAndScolarships(void* data){

    int entryId = 1;
    printHeader();

    Node * ptr = head;			//premier element

    ListItemsPerSpecialityAndScolarshipsParams* params = (ListItemsPerSpecialityAndScolarshipsParams *) data;

    while (ptr != NULL){

        sem_wait(&mutex);
        //L'item a un numero sequentiel dans l'interval defini
        if ((strcmp(ptr->member.speciality,params->speciality) == 0) && (strcmp(ptr->member.scholarships,params->scholarships) == 0)){
            printf("%d: %s \t\t  %s \t\t %s \t\t  %d\n",
                entryId,
                ptr->member.nickname, ptr->member.speciality,
                ptr->member.scholarships, ptr->member.experience
            );
        }

        ptr = ptr->next;
        entryId++;

        sem_post(&mutex);

    }
    printFooter();
    return NULL;
}

//#######################################
//#
//# Affiche les informations des membres pour une specialite formation et experience
void* listItemsPerSpecialityScolarshipsAndExperienceInverval(void* data){

    int entryId = 1;
    printHeader();
    Node * ptr = head;			//premier element

    ListItemsPerSpecialityScolarshipsAndExperienceInvervalParams* params = (ListItemsPerSpecialityScolarshipsAndExperienceInvervalParams *) data;

    while (ptr != NULL){

        sem_wait(&mutex);
        //L'item a un numero sequentiel dans l'interval defini
        if ((strcmp(ptr->member.speciality, params->speciality) == 0) && (strcmp(ptr->member.scholarships, params->scholarships) == 0) && ((ptr->member.experience >= params->start) && (ptr->member.experience <= params->end))){
            printf("%d: %s \t\t  %s \t\t %s \t\t  %d\n",
                entryId,
                ptr->member.nickname, ptr->member.speciality,
                ptr->member.scholarships, ptr->member.experience
            );
        }

        ptr = ptr->next;
        entryId++;

        sem_post(&mutex);

    }
    printFooter();
    return NULL;
}

//#######################################
//#
//# Transmission d'un message aux membres d'un groupe
//#
void* sendTextToGroup(void* data){

    Node * ptr = head;			//premier element

    SendTextToGroupParams* params = (SendTextToGroupParams *) data;


    printf("%s \t %s ",params->nickname, params->group);
    printf("TEXTE ENVOYE: %s\n", params->text);

    while (ptr != NULL){
        sem_wait(&mutex);
        if((strcmp(ptr->member.nickname, params->nickname) != 0) && ((strcmp(ptr->member.speciality, params->group) == 0) || (strcmp(ptr->member.scholarships, params->group) == 0)))
        {
            printf("membre: %s \t transmet au groupe: %s",ptr->member.nickname, ptr->member.speciality);
            printf("   TEXTE ENVOYE/RECU: %s\n", params->text);
        }
        ptr = ptr->next;
        sem_post(&mutex);
    }

    return NULL;
}

//#######################################
//#
//# Transmission d'un message personnel a un membre
//#
void* sendTextBetweenMembers(void* data){

    Node * ptr = head;			//premier element

    SendTextBetweenMembersParams* params = (SendTextBetweenMembersParams *) data;

    printf("%s \t %s ", params->nickname1, params->nickname2);
    printf("TEXTE ENVOYE: %s\n", params->text);

    while (ptr != NULL){
        sem_wait(&mutex);
        if((strcmp(ptr->member.nickname, params->nickname1) != 0) && (strcmp(ptr->member.nickname, params->nickname2) == 0))
        {
            printf(" membre: %s \t transmet au membre: %s ", params->nickname1, params->nickname2);
            printf("TEXTE ENVOYE/RECU: %s\n", params->text);
        }
        ptr = ptr->next;
        sem_post(&mutex);
    }

    return NULL;
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
