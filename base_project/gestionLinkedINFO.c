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
#include <ctype.h>
#define MAX_BUFFER_SIZE 100

extern Node* head;
extern Node* queue;

void error(const int exitcode, const char * message) {
    printf("\nERREUR : \n->\t%s\n", message);
    exit(exitcode);
}

void* readTrans(char* filename) {
    FILE *file;
    char buffer[MAX_BUFFER_SIZE];
    char *tok, *splitPointer;

    file = fopen(filename, "rt");
    if (file == NULL) {
        error(2, "readTrans: Erreur lors de l'ouverture du fichier.");
    }

    fgets(buffer, MAX_BUFFER_SIZE, file);

    while (!feof(file)) {

        tok = strtok_r(buffer, " ", &splitPointer);

        switch(tok[0]) {
            case 'A':
            case 'a':{
                Member member;
                strcpy(member.nickname, strtok_r(NULL, " ", &splitPointer));
                strcpy(member.speciality, strtok_r(NULL, " ", &splitPointer));
                strcpy(member.scholarships, strtok_r(NULL, " ", &splitPointer));
                member.experiences = atoi(strtok_r(NULL, "\n", &splitPointer));
                addMemberItem(member);
                break;
            }
            case 'M':
            case 'm':{
                int nodeIndex = atoi(strtok_r(NULL, " ", &splitPointer));
                Member member;
                strcpy(member.nickname, strtok_r(NULL, " ", &splitPointer));
                strcpy(member.speciality, strtok_r(NULL, " ", &splitPointer));
                strcpy(member.scholarships, strtok_r(NULL, " ", &splitPointer));
                member.experiences = atoi(strtok_r(NULL, "\n", &splitPointer));
                modifyMemberItem(nodeIndex, member);
                break;
            }
            case 'E':
            case 'e':{
                char *nickname = strtok_r(NULL, "\n", &splitPointer);
                removeItem(nickname);
                break;
            }
            case 'L':
            case 'l':{
                char *type = strtok_r(NULL, " ", &splitPointer);

                if (type[0] == 'C') {
                    int startIndex = atoi(strtok_r(NULL, "-", &splitPointer));
                    int endIndex = atoi(strtok_r(NULL, "\n", &splitPointer));

                    listAllItems(startIndex, endIndex);
                }else if (type[0] == 'S') {
                    char* speciality = strtok_r(NULL, "^M", &splitPointer);

                    listItemsBySpecialities(speciality);
                } else if (strcmp(type, "SE") == 0) {
                    char* speciality = strtok_r(NULL, " ", &splitPointer);
                    int startIndex = atoi(strtok_r(NULL, "-", &splitPointer));
                    int endIndex = atoi(strtok_r(NULL, "\n", &splitPointer));

                    listItemsBySpecialitiesExperiences(speciality, startIndex, endIndex);
                } else if (strcmp(type, "SF") == 0) {
                    char* speciality = strtok_r(NULL, " ", &splitPointer);
                    char* scholarships = strtok_r(NULL, "\n", &splitPointer);

                    listItemsBySpecialitiesScholarships(speciality, scholarships);
                } else if (strcmp(type, "SFE") == 0) {
                    char* speciality = strtok_r(NULL, " ", &splitPointer);
                    char* scholarships = strtok_r(NULL, " ", &splitPointer);
                    int startIndex = atoi(strtok_r(NULL, "-", &splitPointer));
                    int endIndex = atoi(strtok_r(NULL, "\n", &splitPointer));

                    listItemsBySpecialitiesScholarshipsExperiences(speciality, scholarships, startIndex, endIndex);
                }
                break;
            }
            case 'T':
            case 't':{
                char *type = strtok_r(NULL, " ", &splitPointer);

                if (strcmp(type, "PG") == 0) {
                    char *nickname = strtok_r(NULL, " ", &splitPointer);
                    char *group = strtok_r(NULL, " ", &splitPointer);
                    char *text = strtok_r(NULL, "\n", &splitPointer);

                    transTextGroupe(nickname, group, text);

                } else if (strcmp(type, "PP") == 0)  {
                    char *sender = strtok_r(NULL, " ", &splitPointer);
                    char *receiver = strtok_r(NULL, " ", &splitPointer);
                    char *text = strtok_r(NULL, "\n", &splitPointer);

                    transTextPersonnel(sender, receiver, text);
                }
                break;
            }

        }
        fgets(buffer, MAX_BUFFER_SIZE, file);
    }
    fclose(file);
    return NULL;
}
