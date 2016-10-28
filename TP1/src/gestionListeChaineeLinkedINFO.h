#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

extern sem_t mutex;

typedef struct member {
    char nickname[100];
    char speciality[100];
    char scholarships[100];
    int experience;
} Member;

struct node {
    Member member;
    struct node *next;
};
typedef struct node Node;


//TODO: Lire s'il ne faudrait pas mieux mettre des const à chaque attributs des structs
typedef struct addItemParams {
    Member member;
} AddItemParams;

typedef struct modifyItemParams {
    int nodeId;
    Member member;
} ModifyItemParams;

typedef struct removeItemParams {
    char* nickname;
} RemoveItemParams;

typedef struct listItemsWithinIntervalParams {
    int start;
    int end;
} ListItemsWithinIntervalParams;

typedef struct listItemsPerSpecialityParams {
    char* speciality;
} ListItemsPerSpecialityParams;

typedef struct listItemsPerSpecialityAndExperienceIntervalParams {
    char* speciality;
    int start;
    int end;
} ListItemsPerSpecialityAndExperienceIntervalParams;

typedef struct listItemsPerSpecialityAndScolarshipsParams {
    char* speciality;
    char* scholarships;
}  ListItemsPerSpecialityAndScolarshipsParams;

typedef struct listItemsPerSpecialityScolarshipsAndExperienceInvervalParams {
    char* speciality;
    char* scholarships;
    int start;
    int end;
} ListItemsPerSpecialityScolarshipsAndExperienceInvervalParams;

typedef struct sendTextToGroupParams{
    char* nickname;
    char* group;
    char* text;
} SendTextToGroupParams;

typedef struct sendTextBetweenMembersParams{
    char* nickname1;
    char* nickname2;
    char* text;
} SendTextBetweenMembersParams;

void error(const int exitcode, const char * message);

void* readTransactionsFile(char* filename);

Node * findPrevious(const char* nickname);
void printHeader();
void printFooter();
void* addItem(void* data);
void* modifyItem(void* data);
void* removeItem(void* data);
void* listItemsWithinInterval(void* data);
void* listItemsPerSpeciality(void* data);
void* listItemsPerSpecialityAndExperienceInterval(void* data);
void* listItemsPerSpecialityAndScolarships(void* data);
void* listItemsPerSpecialityScolarshipsAndExperienceInverval(void* data);
void* sendTextToGroup(void* data); // groupes possibles: Formation ou Specialite
void* sendTextBetweenMembers(void* data);
