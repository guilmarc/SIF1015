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




//#######################################
//#
//# fonction utilisee par les threads de transactions
//#
void* readTransactionsFile(char* filename){
    FILE *file;
    char buffer[100];
    char *tok, *sp;

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

                //TODO: Trouver pourquoi ce type d'initialisation ne peut fonctionner
                //Member member = {nickname, speciality, scholarships, experience};

                //Appel de la fonction associee
                pthread_t threadId;
                pthread_create(&threadId, NULL, addItem, params);

                //TODO: Infaudra créer un tableau au début du main pour conserver les pthread_t
                //et boucler pour faire des join
                //pthread_join(threadId, NULL);

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

                //Remplissage de la structure Modify
                ModifyItemParams* params = (ModifyItemParams*)malloc(sizeof(ModifyItemParams));
                params->nodeId = nodeId;
                strcpy(params->member.nickname, nickname);
                strcpy(params->member.speciality, speciality);
                strcpy(params->member.scholarships, scholarships);
                params->member.experience = experience;

                pthread_t threadId;
                pthread_create(&threadId, NULL, modifyItem, params);
                pthread_join(threadId, NULL);

                break;
            }
            case 'E':
            case 'e':{
                //Extraction du parametre
                char *nickname = strtok_r(NULL, "\n", &sp);

                //Appel de la fonction associee
                removeItem(nickname);
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
                    listItemsWithinInterval(nstart, nend);
                }
                else if(strcmp(ptrType, "S") == 0) // affichage par specialite
                {
                    char* speciality = strtok_r(NULL, "\n", &sp);
                    //Appel de la fonction associee
                    listItemsPerSpeciality(speciality);
                }
                else if(strcmp(ptrType, "SE") == 0) // affichage par specialite et experience
                {
                    char* speciality = strtok_r(NULL, " ", &sp);
                    int nstart = atoi(strtok_r(NULL, "-", &sp));
                    int nend = atoi(strtok_r(NULL, "\n", &sp));
                    //Appel de la fonction associee
                    listItemsPerSpecialityAndExperienceInterval(speciality, nstart, nend);
                }
                else if(strcmp(ptrType, "SF") == 0) // affichage par specialite et formation
                {
                    char* speciality = strtok_r(NULL, " ", &sp);
                    char* scholarships = strtok_r(NULL, "\n", &sp);
                    //Appel de la fonction associee
                    listItemsPerSpecialityAndScolarships(speciality, scholarships);
                }
                else if(strcmp(ptrType, "SFE") == 0) // affichage par specialite formation et experience
                {
                    char* speciality = strtok_r(NULL, " ", &sp);
                    char* scholarships = strtok_r(NULL, " ", &sp);
                    int nstart = atoi(strtok_r(NULL, "-", &sp));
                    int nend = atoi(strtok_r(NULL, "\n", &sp));
                    //Appel de la fonction associee
                    listItemsPerSpecialityScolarshipsAndExperienceInverval(speciality, scholarships, nstart, nend);
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

                    //Appel de la fonction associee
                    sendTextToGroup(nickname, group,text);
                }
                else if(strcmp(ptrType, "PP") == 0) // affichage complet
                {
                    char *nickname1 = strtok_r(NULL, " ", &sp);
                    char *nickname2 = strtok_r(NULL, " ", &sp);
                    char *text = strtok_r(NULL, "\n", &sp);

                    //Appel de la fonction associee
                    sendTextBetweenMembers(nickname1, nickname2,text);
                }
                break;
            }

        }

        //Lecture (tentative) de la prochaine ligne de texte
        fgets(buffer, 100, file);
    }
    //Fermeture du fichier
    fclose(file);
    //Retour
    return NULL;
}
