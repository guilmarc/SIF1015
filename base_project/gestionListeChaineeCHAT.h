#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

struct infoMembre{						
	char nickname[100];
	char group[100];							
	};								 

struct noeud{			
	struct infoMembre membre;		
	struct noeud		*next;	
	};	
	
void error(const int exitcode, const char * message);

void* readTransCHAT(char* nomFichier);

struct noeud * findPrevCHAT(const char* nickname, const char* group);

void addItemCHAT(const char* nickname, const char* group);
void modifyItemCHAT(const int groupIde, const char* nickname, const char* group);
void removeItemCHAT(const char* nickname, const char* group);
void listItemsCHAT(const int start, const int end);
void transTextCHAT(const char* nickname, const char* group, const char* text);