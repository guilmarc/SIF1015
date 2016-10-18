#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "main.h"
#include "linked_list.h"
#include "member.h"

const char FILEPATH[] = "trans2.txt";
const char FILEOPEN_METHOD[] = "r";
const int MAX_BUFFER_SIZE = 1024;

int main(int argc, char **argv) {
    Node* node = createNode();
    loadFile(node);
    displayAll(node);
    return 0;
}

void loadFile(Node* headNode) {
    printf("Reading file\n");
    FILE *file = fopen(FILEPATH, FILEOPEN_METHOD);
    if (file != NULL) {
        char buffer[MAX_BUFFER_SIZE];
    	char *tok, *sp;
        fgets(buffer, 100, file);
    	while(!feof(file)){
    		tok = strtok_r(buffer, " ", &sp);
    		switch(tok[0]){
    			case 'A':
    			case 'a':{
                    Member* member = createMember();
    				strcpy(member->nickname, strtok_r(NULL, " ", &sp));
    				strcpy(member->speciality, strtok_r(NULL, " ", &sp));
    				strcpy(member->scholarships, strtok_r(NULL, " ", &sp));
    				member->experiences = atoi(strtok_r(NULL, "\n", &sp));
                    appendNode(headNode, member);
    				break;
                }
    			case 'M':
    			case 'm':{
    				int noNoeud = atoi(strtok_r(NULL, " ", &sp));
    				char *ptrNick = strtok_r(NULL, " ", &sp);
    				char *ptrSpecialite = strtok_r(NULL, " ", &sp);
    				char *ptrFormation = strtok_r(NULL, " ", &sp);
    				int experience = atoi(strtok_r(NULL, "\n", &sp));
    				break;
                }
    			case 'E':
    			case 'e':{
    				char *ptrNick = strtok_r(NULL, "\n", &sp);
    				break;
                }
    			case 'L':
    			case 'l':{
    				char *ptrType = strtok_r(NULL, " ", &sp);

    				if(ptrType[0] == 'C') // affichage complet
    				{
    					int nstart = atoi(strtok_r(NULL, "-", &sp));
    					int nend = atoi(strtok_r(NULL, "\n", &sp));
    				}
    				else if(ptrType[0] == 'S') // affichage par specialite
    				{
    					char* ptrSpecialite = strtok_r(NULL, "^M", &sp);
    				}
    				else if(strcmp(ptrType, "SE") == 0) // affichage par specialite et experience
    				{
    					char* ptrSpecialite = strtok_r(NULL, " ", &sp);
    					int nstart = atoi(strtok_r(NULL, "-", &sp));
    					int nend = atoi(strtok_r(NULL, "\n", &sp));
    				}
    				else if(strcmp(ptrType, "SF") == 0) // affichage par specialite et formation
    				{
    					char* ptrSpecialite = strtok_r(NULL, " ", &sp);
    					char* ptrFormation = strtok_r(NULL, "\n", &sp);
    				}
    				else if(strcmp(ptrType, "SFE") == 0) // affichage par specialite formation et experience
    				{
    					char* ptrSpecialite = strtok_r(NULL, " ", &sp);
    					char* ptrFormation = strtok_r(NULL, " ", &sp);
    					int nstart = atoi(strtok_r(NULL, "-", &sp));
    					int nend = atoi(strtok_r(NULL, "\n", &sp));
    				}
    				break;
                }
    			case 'T':
    			case 't':{
    				char *ptrType = strtok_r(NULL, " ", &sp);

    				if(strcmp(ptrType, "PG") == 0) // affichage complet
    				{
    					char *ptrNick = strtok_r(NULL, " ", &sp);
    					char *ptrGroupe = strtok_r(NULL, " ", &sp);
    					char *ptrTexte = strtok_r(NULL, "\n", &sp);
    				}
    				else if(strcmp(ptrType, "PP") == 0) // affichage complet
    				{
    					char *ptrNick1 = strtok_r(NULL, " ", &sp);
    					char *ptrNick2 = strtok_r(NULL, " ", &sp);
    					char *ptrTexte = strtok_r(NULL, "\n", &sp);
        			}
        			break;
                }
    	    }
    		fgets(buffer, 100, file);
        }
        fclose(file);
    } else {
        printf("Cannot open file %s\n", FILEPATH);
    }
}
