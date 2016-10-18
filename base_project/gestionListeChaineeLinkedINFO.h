#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

struct Member {
	char ptrNick[100];
	char ptrSpecialite[100];
	char ptrFormation[100];
	int Experience;
} typedef Member;

struct node{
	Member membre;
	struct node *next;
};

typedef struct node Node;

void error(const int exitcode, const char * message);

void* readTranslinkedINFO(char* nomFichier);

Node * findPrevlinkedINFO(const char* ptrNick); // ptrNick unique

void addItemlinkedINFO(const char* ptrNick, const char* ptrSpecialite, const char* ptrFormation, const int Experience);
void modifyItemlinkedINFO(const int noNoeud, const char* ptrNick, const char* ptrSpecialite, const char* ptrFormation, const int Experience);
void removeItemlinkedINFO(const char* ptrNick);
void listItemsCompletlinkedINFO(const int start, const int end);
void listItemsParSpecialitelinkedINFO(const char* ptrSpecialite);
void listItemsParSpecialiteExperiencelinkedINFO(const char* ptrSpecialite, const int start, const int end);
void listItemsParSpecialiteFormationlinkedINFO(const char* ptrSpecialite, const char* ptrFormation);
void listItemsParSpecialiteFormationExperiencelinkedINFO(const char* ptrSpecialite, const char* ptrFormation, const int start, const int end );
void transTextGroupelinkedINFO(const char* ptrNick, const char* ptrGroupe, const char* ptrTexte); // groupes possibles: Formation ou Specialite
void transTextPersonnellinkedINFO(const char* ptrNick1, const char* ptrNick2, const char* ptrTexte);

void printHeader();
void printFooter();
