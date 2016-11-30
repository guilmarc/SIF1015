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

#include "linkedList.h"

//Pointeur de tete de liste
extern Node *head;
//Pointeur de queue de liste pour ajout rapide
extern Node *queue;



//#######################################
//#
//# fonction utilisee par les threads de transactions
//#

void *parseTransaction(char *transaction, char *client_fifo) {

    char *tok, *sp;

    pthread_t thread;

    //Extraction du type de transaction
    tok = strtok_r(transaction, " ", &sp);

    //Branchement selon le type de transaction
    switch (tok[0]) {
        case 'A':
        case 'a': {
            //Extraction des parametres
            char *nickname = strtok_r(NULL, " ", &sp);
            char *speciality = strtok_r(NULL, " ", &sp);
            char *scholarships = strtok_r(NULL, " ", &sp);
            int experience = atoi(strtok_r(NULL, "\n", &sp));   //atoi = AsciiToInteger

            Member *member = (Member *) malloc(sizeof(Member));
            strcpy(member->nickname, nickname);
            strcpy(member->speciality, speciality);
            strcpy(member->scholarships, scholarships);
            member->experience = experience;

            AddItemParams *params = (AddItemParams *) malloc(sizeof(AddItemParams));
            strcpy(params->client_fifo, client_fifo);
            params->member = *member;

            //Appel de la fonction associee
            //pthread_create(&thread, NULL, addItem, params);

            return addItem(params);

            break;
        }
        case 'E':
        case 'e': {
            //Extraction du parametre
            char *nickname = strtok_r(NULL, "\n", &sp);

            //Remplissage de la structure de paramètres
            RemoveItemParams *params = (RemoveItemParams *) malloc(sizeof(RemoveItemParams));
            params->nickname = nickname;

            //pthread_create(&thread, NULL, removeItem, params);
            return removeItem(params);

            break;
        }
        case 'L':
        case 'l': {
            //Extraction des parametres
            char *ptrType = strtok_r(NULL, " ", &sp);

            if (strcmp(ptrType, "C") == 0) // affichage complet
            {
                int nstart = atoi(strtok_r(NULL, "-", &sp));
                int nend = atoi(strtok_r(NULL, "\n", &sp));

                //Remplissage de la structure de paramètres
                ListItemsWithinIntervalParams *params = (ListItemsWithinIntervalParams *) malloc(
                        sizeof(ListItemsWithinIntervalParams));
                params->start = nstart;
                params->end = nend;

                //Appel de la fonction associee
                //pthread_create(&thread, NULL, listItemsWithinInterval, params);
                return listItemsWithinInterval(params);
            } else if (strcmp(ptrType, "S") == 0) // affichage par specialite
            {
                char *speciality = strtok_r(NULL, "\n", &sp);

                //Remplissage de la structure de paramètres
                ListItemsPerSpecialityParams *params = (ListItemsPerSpecialityParams *) malloc(
                        sizeof(ListItemsPerSpecialityParams));
                params->speciality = speciality;

                //Appel de la fonction associee
                //pthread_create(&thread, NULL, listItemsPerSpeciality, params);
                return listItemsPerSpeciality(params);
            } else if (strcmp(ptrType, "SE") == 0) // affichage par specialite et experience
            {
                char *speciality = strtok_r(NULL, " ", &sp);
                int nstart = atoi(strtok_r(NULL, "-", &sp));
                int nend = atoi(strtok_r(NULL, "\n", &sp));

                //Remplissage de la structure de paramètres
                ListItemsPerSpecialityAndExperienceIntervalParams *params = (ListItemsPerSpecialityAndExperienceIntervalParams *) malloc(
                        sizeof(ListItemsPerSpecialityAndExperienceIntervalParams));
                params->speciality = speciality;
                params->start = nstart;
                params->end = nend;

                //Appel de la fonction associee
                //pthread_create(&thread, NULL, listItemsPerSpecialityAndExperienceInterval, params);
                return listItemsPerSpecialityAndExperienceInterval(params);
            } else if (strcmp(ptrType, "SF") == 0) // affichage par specialite et formation
            {
                char *speciality = strtok_r(NULL, " ", &sp);
                char *scholarships = strtok_r(NULL, "\n", &sp);

                //Remplissage de la structure de paramètres
                ListItemsPerSpecialityAndScolarshipsParams *params = (ListItemsPerSpecialityAndScolarshipsParams *) malloc(
                        sizeof(ListItemsPerSpecialityAndScolarshipsParams));
                params->speciality = speciality;
                params->scholarships = scholarships;

                //Appel de la fonction associee
                //pthread_create(&thread, NULL, listItemsPerSpecialityAndScolarships, params);
                return listItemsPerSpecialityAndScolarships(params);


            } else if (strcmp(ptrType, "SFE") == 0) // affichage par specialite formation et experience
            {
                char *speciality = strtok_r(NULL, " ", &sp);
                char *scholarships = strtok_r(NULL, " ", &sp);
                int nstart = atoi(strtok_r(NULL, "-", &sp));
                int nend = atoi(strtok_r(NULL, "\n", &sp));

                //Remplissage de la structure de paramètres
                ListItemsPerSpecialityScolarshipsAndExperienceInvervalParams *params = (ListItemsPerSpecialityScolarshipsAndExperienceInvervalParams *) malloc(
                        sizeof(ListItemsPerSpecialityScolarshipsAndExperienceInvervalParams));
                params->speciality = speciality;
                params->scholarships = scholarships;
                params->start = nstart;
                params->end = nend;

                //Appel de la fonction associee
                //pthread_create(&thread, NULL, listItemsPerSpecialityScolarshipsAndExperienceInverval, params);
                return listItemsPerSpecialityScolarshipsAndExperienceInverval(params);
            }
            break;
        }
        case 'T':
        case 't': {

            //Extraction des parametres
            char *ptrType = strtok_r(NULL, " ", &sp);

            if (strcmp(ptrType, "PG") == 0) // affichage complet
            {
                char *nickname = strtok_r(NULL, " ", &sp);
                char *group = strtok_r(NULL, " ", &sp);
                char *text = strtok_r(NULL, "\n", &sp);

                //Remplissage de la structure de paramètres
                SendTextToGroupParams *params = (SendTextToGroupParams *) malloc(sizeof(SendTextToGroupParams));
                params->nickname = nickname;
                params->group = group;
                params->text = text;

                //Appel de la fonction associee
                //pthread_create(&thread, NULL, listItemsPerSpecialityScolarshipsAndExperienceInverval, params);
                return listItemsPerSpecialityScolarshipsAndExperienceInverval(params);
            } else if (strcmp(ptrType, "PP") == 0) // affichage complet
            {
                char *nickname1 = strtok_r(NULL, " ", &sp);
                char *nickname2 = strtok_r(NULL, " ", &sp);
                char *text = strtok_r(NULL, "\n", &sp);

                //Remplissage de la structure de paramètres
                SendTextBetweenMembersParams *params = (SendTextBetweenMembersParams *) malloc(
                        sizeof(SendTextBetweenMembersParams));
                params->nickname1 = nickname1;
                params->nickname2 = nickname2;
                params->text = text;

                //Appel de la fonction associee
                //pthread_create(&thread, NULL, sendTextBetweenMembers, params);
                return sendTextBetweenMembers(params);
            }
            break;
        }

    }

    return NULL;

}
