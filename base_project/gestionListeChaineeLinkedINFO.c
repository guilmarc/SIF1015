#include "gestionListeChaineeLinkedINFO.h"

extern Node* head;
extern Node* queue;

Node * findPrevlinkedINFO(const char* ptrNick){
    if ((head != NULL) || (queue != NULL)){
        Node * ptr = head;
        while (ptr->next!=NULL){

            printf("\n dans findPrevlinkedINFO  nick suivant %s NICK %s COMPARAISON %d %d", ptr->next->membre.ptrNick,ptrNick, (int)(strlen(ptr->next->membre.ptrNick)), (int)(strlen(ptrNick)));

            //Est-ce le predecesseur de l'item recherche?
            if((strcmp(ptr->next->membre.ptrNick,ptrNick) == 0) ){

                //On retourne un pointeur sur l'item precedent
                return ptr;
            }

            //Deplacement du pointeur de navigation
            ptr=ptr->next;
        }
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
    Node* ni = (Node*)malloc(sizeof(Node));


    //Affectation des valeurs des champs
    strcpy(ni->membre.ptrNick, ptrNick);
    strcpy(ni->membre.ptrSpecialite, ptrSpecialite);
    strcpy(ni->membre.ptrFormation, ptrFormation);
    ni->membre.Experience = Experience;


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


    Node * ptr = head;			//premier element


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
            ptr = ptr->next;
            noentree++;
        }

    }

}


//#######################################
//#
//# Retire un item de la liste chainee
//#
void removeItemlinkedINFO(const char* ptrNick){
    Node * ptr;
    Node * optr;

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
            head = ptr->next;
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
            if (queue==ptr->next) // suppression de l'element de queue
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
    }
}


//#######################################
//#
//# Affiche les informations des membres dont le numero sequentiel est compris dans un intervalle
//#
void listItemsCompletlinkedINFO(const int start, const int end){

    int noentree=1;
    printHeader();

    Node * ptr = head;			//premier element


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
            ptr = ptr->next;
            noentree++;
        }

    }
    printFooter();
}
//#######################################
//#
//# Affiche les informations des membres pour une specialite donnee
void listItemsParSpecialitelinkedINFO(const char* ptrSpecialite){


    int noentree=1;
    printHeader();

    Node * ptr = head;			//premier element


    while (ptr!=NULL){

        //L'item a un numero sequentiel dans l'interval defini
        if ((strcmp(ptr->membre.ptrSpecialite,ptrSpecialite) == 0)){
            printf("%d: %s \t\t  %s \t\t %s \t\t  %d\n",noentree,
            ptr->membre.ptrNick, ptr->membre.ptrSpecialite,
            ptr->membre.ptrFormation, ptr->membre.Experience);
        }
        else{
            ptr = ptr->next;
            noentree++;
        }

    }
    printFooter();
}

//#######################################
//#
//# Affiche les informations des membres pour une specialite et experience
void listItemsParSpecialiteExperiencelinkedINFO(const char* ptrSpecialite, const int start, const int end){

    int noentree=1;
    printHeader();

    Node * ptr = head;			//premier element


    while (ptr!=NULL){

        //L'item a un numero sequentiel dans l'interval defini
        if ((strcmp(ptr->membre.ptrSpecialite,ptrSpecialite) == 0) && ((ptr->membre.Experience >= start) && (ptr->membre.Experience <= end))){
            printf("%d: %s \t\t  %s \t\t %s \t\t  %d\n",noentree,
            ptr->membre.ptrNick, ptr->membre.ptrSpecialite,
            ptr->membre.ptrFormation, ptr->membre.Experience);
        }
        else{
            ptr = ptr->next;
            noentree++;
        }

    }
    printFooter();
}

//#######################################
//#
//# Affiche les informations des membres pour une specialite et formation
void listItemsParSpecialiteFormationlinkedINFO(const char* ptrSpecialite, const char* ptrFormation){

    int noentree=1;
    printHeader();
    Node * ptr = head;			//premier element


    while (ptr!=NULL){

        //L'item a un numero sequentiel dans l'interval defini
        if ((strcmp(ptr->membre.ptrSpecialite,ptrSpecialite) == 0) && (strcmp(ptr->membre.ptrFormation,ptrFormation) == 0)){
            printf("%d: %s \t\t  %s \t\t %s \t\t  %d\n",noentree,
                ptr->membre.ptrNick, ptr->membre.ptrSpecialite,
                ptr->membre.ptrFormation, ptr->membre.Experience);
        }
        else{
            ptr = ptr->next;
            noentree++;
        }

    }
    printFooter();
}

//#######################################
//#
//# Affiche les informations des membres pour une specialite formation et experience
void listItemsParSpecialiteFormationExperiencelinkedINFO(const char* ptrSpecialite, const char* ptrFormation, const int start, const int end ){

    int noentree=1;

    printHeader();

    Node * ptr = head;			//premier element


    while (ptr!=NULL){

        //L'item a un numero sequentiel dans l'interval defini
        if ((strcmp(ptr->membre.ptrSpecialite,ptrSpecialite) == 0) && (strcmp(ptr->membre.ptrFormation,ptrFormation) == 0) && ((ptr->membre.Experience >= start) && (ptr->membre.Experience <= end))){
            printf("%d: %s \t\t  %s \t\t %s \t\t  %d\n",noentree,
            ptr->membre.ptrNick, ptr->membre.ptrSpecialite,
            ptr->membre.ptrFormation, ptr->membre.Experience);
        }
        else{
            ptr = ptr->next;
            noentree++;
        }

    }
    printFooter();
}

//#######################################
//#
//# Transmission d'un message aux membres d'un groupe
//#
void transTextGroupelinkedINFO(const char* ptrNick, const char* ptrGroupe, const char* ptrTexte){


    Node * ptr = head;			//premier element


    printf("%s \t %s ",ptrNick, ptrGroupe);
    printf("TEXTE ENVOYE: %s\n",ptrTexte);

    while (ptr!=NULL){

        if((strcmp(ptr->membre.ptrNick,ptrNick) != 0) && ((strcmp(ptr->membre.ptrSpecialite,ptrGroupe) == 0) || (strcmp(ptr->membre.ptrFormation,ptrGroupe) == 0)))
        {
            printf("membre: %s \t transmet au groupe: %s",ptr->membre.ptrNick, ptr->membre.ptrSpecialite);
            printf("   TEXTE ENVOYE/RECU: %s\n",ptrTexte);
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

//#######################################
//#
//# Transmission d'un message personnel a un membre
//#
void transTextPersonnellinkedINFO(const char* ptrNick1, const char* ptrNick2, const char* ptrTexte){


    Node * ptr = head;			//premier element


    printf("%s \t %s ",ptrNick1, ptrNick2);
    printf("TEXTE ENVOYE: %s\n",ptrTexte);

    while (ptr!=NULL){

        if((strcmp(ptr->membre.ptrNick,ptrNick1) != 0) && (strcmp(ptr->membre.ptrNick,ptrNick2) == 0))
        {
            printf(" membre: %s \t transmet au membre: %s ",ptrNick1, ptrNick2);
            printf("TEXTE ENVOYE/RECU: %s\n",ptrTexte);
        }
        ptr = ptr->next;

    }

}
