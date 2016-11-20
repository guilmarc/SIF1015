#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

//extern sem_t mutex;
extern sem_t head_semaphore;
extern sem_t queue_semaphore;
extern sem_t print_semaphore;

typedef struct {
    char nickname[100];
    char speciality[100];
    char scholarships[100];
    int experience;
} Member;

typedef struct node {
    sem_t semaphore;
    char* client_fifo;
    Member member;
    struct node *next;
} Node;


typedef struct {
    char client_fifo[100];
    Member member;
} AddItemParams;

typedef struct {
    char* nickname;
} RemoveItemParams;

typedef struct {
    int start;
    int end;
} ListItemsWithinIntervalParams;

typedef struct {
    char* speciality;
} ListItemsPerSpecialityParams;

typedef struct {
    char* speciality;
    int start;
    int end;
} ListItemsPerSpecialityAndExperienceIntervalParams;

typedef struct {
    char* speciality;
    char* scholarships;
}  ListItemsPerSpecialityAndScolarshipsParams;

typedef struct {
    char* speciality;
    char* scholarships;
    int start;
    int end;
} ListItemsPerSpecialityScolarshipsAndExperienceInvervalParams;

typedef struct {
    char* nickname;
    char* group;
    char* text;
} SendTextToGroupParams;

typedef struct {
    char* nickname1;
    char* nickname2;
    char* text;
} SendTextBetweenMembersParams;

void error(const int exitcode, const char * message);

void* handleTransaction(char* transaction, char* client_fifo);

int getNumberOfLines(char* filename);

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
