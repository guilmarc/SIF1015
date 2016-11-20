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

#include "linkedList.h"
#include "../../client/src/client.h"

//Pointeur de tete de liste
extern Node* head;
//Pointeur de queue de liste pour ajout rapide
extern Node* queue;

sem_t head_semaphore;
sem_t queue_semaphore;
sem_t print_semaphore;


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

        //Est-ce le predecesseur de l'item recherche?
        //Empêcher à un thread de modifier le champ nickname pendant que l'on compare
        sem_wait(&ptr->semaphore);
        if((strcmp(ptr->next->member.nickname, nickname) == 0) ){
            sem_post(&ptr->semaphore);
            //On retourne un pointeur sur l'item precedent
            return ptr;
        }
        sem_post(&ptr->semaphore);

        //Déplacement du pointeur de navigation
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
void* addItem(void* data) {

    //Creation de l'enregistrement en mémoire
    Node* ni = (Node*)malloc(sizeof(Node));

    AddItemParams* params = (AddItemParams *) data;

    ni->client_fifo = params->client_fifo;
    ni->member = params->member;

    //Initialisation du sémaphore de noeud
    sem_init(&ni->semaphore, 0, 1);

    //Comme il est possible que deux ajouts se fassent en "meme" temps, il faut que le premier qui demande la lecture
    //de la variable head bloque cette variable sinon le code ni->next = NULL sera exécuté plusieurs fois

    //On bloque l'accès à ce noeud qui deviendra soit la head soit la queue de la liste (ou les deux)
    sem_wait(&head_semaphore);
    if(head == NULL) // ajout au debut de la liste vide
    {
        //  premier noeud
        printf("LA HEAD EST NULLE : %s\n", ni->member.nickname);

        ni->next= NULL;
        queue = head = ni;
        sem_post(&head_semaphore);
    }
    else  // ajout a la fin de la liste
    {

        printf("ON CONTINUE : %s\n", ni->member.nickname);
        sem_wait(&queue_semaphore);
        Node* tptr = queue;
        ni->next= NULL;
        queue = ni;
        tptr->next = ni;
        sem_post(&queue_semaphore);
    }

    Info_FIFO_Transaction *structure = (Info_FIFO_Transaction*)malloc(sizeof(Info_FIFO_Transaction));
    strcpy(structure->transaction, "Connecté au serveur avec succès !");
    return structure;

    pthread_exit(0);
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

    //On bloque la tête de la liste le temps de la comparaison pour pas qu'un autre thread lo modifie.
    sem_wait(&head->semaphore);
    if(strcmp(head->member.nickname,params->nickname) == 0)
    {
        //3head->semaphore


        ptr = head; // suppression du premier element de la liste

        if(head == ptr) // suppression de l'element de tete
        {
            if(head == queue) // un seul element dans la liste
            {
                free(ptr);
                queue = head = NULL;
                return NULL;
            }
            head = ptr->next;
            //printf("tete\n");
            free(ptr);
        }

        sem_post(&head->semaphore);
    }
    else
    {
        //On libère le node head
        sem_post(&head->semaphore);

        ptr = findPrevious(params->nickname); // ptr pointe sur l'element precedent de celui a supprimer

        //Item  trouve
        if (ptr != NULL)
        {
            sem_wait(&ptr->semaphore);
            if (queue == ptr->next) // suppression de l'element de queue
            {
                sem_wait(&queue->semaphore);
                queue = ptr;
                free(ptr->next);
                ptr->next = NULL;
                sem_post(&queue->semaphore);
                //printf("queue\n");
                return NULL;
            }
            else // suppression d'un element dans la liste
            {
                sem_wait(&ptr->next->semaphore);
                optr = ptr->next;
                ptr->next = ptr->next->next;

                free(optr);
            }
            sem_post(&ptr->semaphore);
        }

    }
    return NULL;
}


//#######################################
//#
//# Affiche les informations des membres dont le numero sequentiel est compris dans un intervalle
//#
void* listItemsWithinInterval(void* data){
    sem_wait(&print_semaphore);
    int entryId=1;
    printHeader();

    Node * ptr = head;			//premier element

    ListItemsWithinIntervalParams* params = (ListItemsWithinIntervalParams *) data;

    while (ptr != NULL){

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

    }
    printFooter();
    sem_post(&print_semaphore);
    return NULL;
}
//#######################################
//#
//# Affiche les informations des membres pour une specialite donnee
void* listItemsPerSpeciality(void* data){

    sem_wait(&print_semaphore);

    int entryId = 1;
    printHeader();

    Node * ptr = head;			//premier element

    ListItemsPerSpecialityParams* params = (ListItemsPerSpecialityParams *) data;

    while (ptr != NULL){

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
    }
    printFooter();
    sem_post(&print_semaphore);
    return NULL;
}

//#######################################
//#
//# Affiche les informations des membres pour une specialite et experience
void* listItemsPerSpecialityAndExperienceInterval(void* data){
    sem_wait(&print_semaphore);
    int entryId = 1;
    printHeader();
    Node * ptr = head;			//premier element

    ListItemsPerSpecialityAndExperienceIntervalParams* params = (ListItemsPerSpecialityAndExperienceIntervalParams *) data;

    while (ptr != NULL){

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

    }
    printFooter();
    sem_post(&print_semaphore);
    return NULL;
}

//#######################################
//#
//# Affiche les informations des membres pour une specialite et formation
void* listItemsPerSpecialityAndScolarships(void* data){
    sem_wait(&print_semaphore);
    int entryId = 1;
    printHeader();

    Node * ptr = head;			//premier element

    ListItemsPerSpecialityAndScolarshipsParams* params = (ListItemsPerSpecialityAndScolarshipsParams *) data;

    while (ptr != NULL){

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

    }
    printFooter();
    sem_post(&print_semaphore);
    return NULL;
}

//#######################################
//#
//# Affiche les informations des membres pour une specialite formation et experience
void* listItemsPerSpecialityScolarshipsAndExperienceInverval(void* data){
    sem_wait(&print_semaphore);

    int entryId = 1;
    printHeader();
    Node * ptr = head;			//premier element

    ListItemsPerSpecialityScolarshipsAndExperienceInvervalParams* params = (ListItemsPerSpecialityScolarshipsAndExperienceInvervalParams *) data;

    while (ptr != NULL){

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


    }
    printFooter();
    sem_post(&print_semaphore);
    return NULL;
}

//#######################################
//#
//# Transmission d'un message aux membres d'un groupe
//#
void* sendTextToGroup(void* data){

    sem_wait(&print_semaphore);
    Node * ptr = head;			//premier element

    SendTextToGroupParams* params = (SendTextToGroupParams *) data;


    printf("%s \t %s ",params->nickname, params->group);
    printf("TEXTE ENVOYE: %s\n", params->text);

    while (ptr != NULL){
        if((strcmp(ptr->member.nickname, params->nickname) != 0) && ((strcmp(ptr->member.speciality, params->group) == 0) || (strcmp(ptr->member.scholarships, params->group) == 0)))
        {
            printf("membre: %s \t transmet au groupe: %s",ptr->member.nickname, ptr->member.speciality);
            printf("   TEXTE ENVOYE/RECU: %s\n", params->text);
        }
        ptr = ptr->next;
    }

    sem_post(&print_semaphore);
    return NULL;
}

//#######################################
//#
//# Transmission d'un message personnel a un membre
//#
void* sendTextBetweenMembers(void* data){

    sem_wait(&print_semaphore);
    Node * ptr = head;			//premier element

    SendTextBetweenMembersParams* params = (SendTextBetweenMembersParams *) data;

    printf("%s \t %s ", params->nickname1, params->nickname2);
    printf("TEXTE ENVOYE: %s\n", params->text);

    while (ptr != NULL){
        if((strcmp(ptr->member.nickname, params->nickname1) != 0) && (strcmp(ptr->member.nickname, params->nickname2) == 0))
        {
            printf(" membre: %s \t transmet au membre: %s ", params->nickname1, params->nickname2);
            printf("TEXTE ENVOYE/RECU: %s\n", params->text);
        }
        ptr = ptr->next;
    }

    sem_post(&print_semaphore);
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
