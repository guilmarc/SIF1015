#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

typedef struct member {
    char nickname[100];
    char speciality[100];
    char scholarships[100];
    int Experience;
} Member;

struct node {
    Member membre;
    struct node *next;
};

typedef struct node Node;


void error(const int exitcode, const char * message);

void* readTranslinkedINFO(char* nomFichier);

Node * findPrevlinkedINFO(const char* nickname);
void printHeader();
void printFooter();
void* addItemlinkedINFO(void* data);
void modifyItemlinkedINFO(const int noNoeud, const char* nickname, const char* speciality, const char* scholarships, const int Experience);
void removeItemlinkedINFO(const char* nickname);
void listItemsCompletlinkedINFO(const int start, const int end);
void listItemsParSpecialitelinkedINFO(const char* speciality);
void listItemsParSpecialiteExperiencelinkedINFO(const char* speciality, const int start, const int end);
void listItemsParSpecialiteFormationlinkedINFO(const char* speciality, const char* scholarships);
void listItemsParSpecialiteFormationExperiencelinkedINFO(const char* speciality, const char* scholarships, const int start, const int end );
void transTextGroupelinkedINFO(const char* nickname, const char* group, const char* text); // groupes possibles: Formation ou Specialite
void transTextPersonnellinkedINFO(const char* nickname1, const char* nickname2, const char* text);
