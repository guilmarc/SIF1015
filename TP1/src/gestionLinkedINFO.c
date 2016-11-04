//#########################################################
//#
//# Titre : 	Utilitaires CHAT LINUX Automne 16
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

//Pointeur de tete de liste
extern Node* head;
//Pointeur de queue de liste pour ajout rapide
extern Node* queue;

//#######################################
//#
//# Affiche un message et quitte le programme
//#
void error(const int exitcode, const char * message){
    printf("\n-------------------------\n%s\n", message);
    exit(exitcode);
}

int getNumberOfLines(char* filename) {
    FILE* file = fopen(filename, "rt");
    if (file==NULL) {
        error(2, "readTransactionsFile: Erreur lors de l'ouverture du fichier.");
    }

    int ch, number_of_lines = 0;

    do
    {
        ch = fgetc(file);
        if(ch == '\n')
            number_of_lines++;
    } while (ch != EOF);

// last line doesn't end with a new line!
// but there has to be a line at least before the last line
    if(ch != '\n' && number_of_lines != 0)
        number_of_lines++;

    fclose(file);

    return number_of_lines;
}


//#######################################
//#
//# fonction utilisee par les threads de transactions
//#
void* readTransactionsFile(char* filename){
    FILE *file;
    char buffer[100];
    char *tok, *sp;
    int counter = 0;
    int numberOfLines = getNumberOfLines(filename);
    pthread_t threads[numberOfLines];

    //Ouverture du fichier en mode "r" (equiv. "rt") : [r]ead [t]ext
    file = fopen(filename, "rt");
    if (file==NULL) {
        error(2, "readTransactionsFile: Erreur lors de l'ouverture du fichier.");
    }


    //Lecture (tentative) d'une ligne de texte
    fgets(buffer, 100, file);

    //Pour chacune des lignes lues
    while(!feof(file)){

        //Extraction du type de transaction
        tok = strtok_r(buffer, " ", &sp);

        //Branchement selon le type de transaction
        switch(tok[0]){
            case 'A':
            case 'a':{
                //Extraction des parametres
                char *nickname = strtok_r(NULL, " ", &sp);
                char *speciality = strtok_r(NULL, " ", &sp);
                char *scholarships = strtok_r(NULL, " ", &sp);
                int experience = atoi(strtok_r(NULL, "\n", &sp));   //atoi = AsciiToInteger

                Member *member = (Member*)malloc(sizeof(Member));
                strcpy(member->nickname, nickname);
                strcpy(member->speciality, speciality);
                strcpy(member->scholarships, scholarships);
                member->experience = experience;

                AddItemParams *params = (AddItemParams*)malloc(sizeof(AddItemParams));
                params->member  = *member;

                //Appel de la fonction associee
                pthread_create(&threads[counter++], NULL, addItem, params);

                //******************  AVIS AU CORRECTEUR: ***************************
                //Afin d'éviter toute incohérence dans ce TP il faudrait en fait exécuter les fonctions d'ajout en
                //série car sinon on affiche (et modifie) parfois des Membres avant même leur ajout.
                //Pour ce faire il suffit de commenter le pthread_create plus haut et décommenter le code suivant
                //pthread_t thread;
                //pthread_create(&thread, NULL, addItem, params);
                //pthread_join(thread, NULL);
                //******************  AVIS AU CORRECTEUR: ***************************

                break;
            }
            case 'M':
            case 'm':{
                //Extraction des parametres
                int nodeId = atoi(strtok_r(NULL, " ", &sp));
                char *nickname = strtok_r(NULL, " ", &sp);
                char *speciality = strtok_r(NULL, " ", &sp);
                char *scholarships = strtok_r(NULL, " ", &sp);
                int experience = atoi(strtok_r(NULL, "\n", &sp));

                //Remplissage de la structure de paramètres
                ModifyItemParams* params = (ModifyItemParams*)malloc(sizeof(ModifyItemParams));
                params->nodeId = nodeId;
                strcpy(params->member.nickname, nickname);
                strcpy(params->member.speciality, speciality);
                strcpy(params->member.scholarships, scholarships);
                params->member.experience = experience;

                //pthread_create(&threads[counter++], NULL, modifyItem, params);

                break;
            }
            case 'E':
            case 'e':{
                //Extraction du parametre
                char *nickname = strtok_r(NULL, "\n", &sp);

                //Remplissage de la structure de paramètres
                RemoveItemParams* params = (RemoveItemParams*)malloc(sizeof(RemoveItemParams));
                params->nickname = nickname;

                //pthread_create(&threads[counter++], NULL, removeItem, params);

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

                    //Remplissage de la structure de paramètres
                    ListItemsWithinIntervalParams* params = (ListItemsWithinIntervalParams*)malloc(sizeof(ListItemsWithinIntervalParams));
                    params->start = nstart;
                    params->end = nend;

                    //Appel de la fonction associee
                    pthread_create(&threads[counter++], NULL, listItemsWithinInterval, params);
                }
                else if(strcmp(ptrType, "S") == 0) // affichage par specialite
                {
                    char* speciality = strtok_r(NULL, "\n", &sp);

                    //Remplissage de la structure de paramètres
                    ListItemsPerSpecialityParams* params = (ListItemsPerSpecialityParams*)malloc(sizeof(ListItemsPerSpecialityParams));
                    params->speciality = speciality;

                    //Appel de la fonction associee
                    pthread_create(&threads[counter++], NULL, listItemsPerSpeciality, params);
                }
                else if(strcmp(ptrType, "SE") == 0) // affichage par specialite et experience
                {
                    char* speciality = strtok_r(NULL, " ", &sp);
                    int nstart = atoi(strtok_r(NULL, "-", &sp));
                    int nend = atoi(strtok_r(NULL, "\n", &sp));

                    //Remplissage de la structure de paramètres
                    ListItemsPerSpecialityAndExperienceIntervalParams* params = (ListItemsPerSpecialityAndExperienceIntervalParams*)malloc(sizeof(ListItemsPerSpecialityAndExperienceIntervalParams));
                    params->speciality = speciality;
                    params->start = nstart;
                    params->end = nend;

                    //Appel de la fonction associee
                    pthread_create(&threads[counter++], NULL, listItemsPerSpecialityAndExperienceInterval, params);
                }
                else if(strcmp(ptrType, "SF") == 0) // affichage par specialite et formation
                {
                    char* speciality = strtok_r(NULL, " ", &sp);
                    char* scholarships = strtok_r(NULL, "\n", &sp);

                    //Remplissage de la structure de paramètres
                    ListItemsPerSpecialityAndScolarshipsParams* params = (ListItemsPerSpecialityAndScolarshipsParams*)malloc(sizeof(ListItemsPerSpecialityAndScolarshipsParams));
                    params->speciality = speciality;
                    params->scholarships = scholarships;

                    //Appel de la fonction associee
                    pthread_create(&threads[counter++], NULL, listItemsPerSpecialityAndScolarships, params);
                }
                else if(strcmp(ptrType, "SFE") == 0) // affichage par specialite formation et experience
                {
                    char* speciality = strtok_r(NULL, " ", &sp);
                    char* scholarships = strtok_r(NULL, " ", &sp);
                    int nstart = atoi(strtok_r(NULL, "-", &sp));
                    int nend = atoi(strtok_r(NULL, "\n", &sp));

                    //Remplissage de la structure de paramètres
                    ListItemsPerSpecialityScolarshipsAndExperienceInvervalParams* params = (ListItemsPerSpecialityScolarshipsAndExperienceInvervalParams*)malloc(sizeof(ListItemsPerSpecialityScolarshipsAndExperienceInvervalParams));
                    params->speciality = speciality;
                    params->scholarships = scholarships;
                    params->start = nstart;
                    params->end = nend;

                    //Appel de la fonction associee
                    pthread_create(&threads[counter++], NULL, listItemsPerSpecialityScolarshipsAndExperienceInverval, params);
                }
                break;
            }
            case 'T':
            case 't':{

                //Extraction des parametres
                char *ptrType = strtok_r(NULL, " ", &sp);

                if(strcmp(ptrType, "PG") == 0) // affichage complet
                {
                    char *nickname = strtok_r(NULL, " ", &sp);
                    char *group = strtok_r(NULL, " ", &sp);
                    char *text = strtok_r(NULL, "\n", &sp);

                    //Remplissage de la structure de paramètres
                    SendTextToGroupParams* params = (SendTextToGroupParams*)malloc(sizeof(SendTextToGroupParams));
                    params->nickname = nickname;
                    params->group = group;
                    params->text = text;

                    //Appel de la fonction associee
                    pthread_create(&threads[counter++], NULL, sendTextToGroup, params);
                }
                else if(strcmp(ptrType, "PP") == 0) // affichage complet
                {
                    char *nickname1 = strtok_r(NULL, " ", &sp);
                    char *nickname2 = strtok_r(NULL, " ", &sp);
                    char *text = strtok_r(NULL, "\n", &sp);

                    //Remplissage de la structure de paramètres
                    SendTextBetweenMembersParams* params = (SendTextBetweenMembersParams*)malloc(sizeof(SendTextBetweenMembersParams));
                    params->nickname1 = nickname1;
                    params->nickname2 = nickname2;
                    params->text = text;

                    //Appel de la fonction associee
                    pthread_create(&threads[counter++], NULL, sendTextBetweenMembers, params);
                }
                break;
            }

        }

        //Lecture (tentative) de la prochaine ligne de texte
        fgets(buffer, 100, file);
    }
    //Fermeture du fichier
    fclose(file);

    //On s'assure que tous les threads seront terminés avant la fermeture du programme
    //Ici on utilise la variable counter et non numberOfLine car il peut y avoir des lignes vides.
    int i = 0;
    for(i = 0; i< counter; i++) {
        pthread_join(threads[i], NULL);
    }

    //Retour
    return NULL;
}
