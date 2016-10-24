#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

struct Member {
	char nickname[100];
	char speciality[100];
	char scholarships[100];
	int experiences;
} typedef Member;

struct node{
	Member member;
	struct node *next;
};

typedef struct node Node;

void error(const int exitcode, const char * message);

void* readTrans(char* filename);

void parseCommand(char* commandString);

Node * findPrev(const char* nickname); // nickname unique

void addItem(const char* nickname, const char* speciality, const char* scholarships, const int experiences);
void addMemberItem(const Member member);
void modifyItem(const int nodeIndex, const char* nickname, const char* speciality, const char* scholarships, const int experiences);
void modifyMemberItem(const int nodeIndex, const Member member);
void removeItem(const char* nickname);
void listAllItems(const int start, const int end);
void listItemsBySpecialities(const char* speciality);
void listItemsBySpecialitiesExperiences(const char* speciality, const int start, const int end);
void listItemsBySpecialitiesScholarships(const char* speciality, const char* scholarships);
void listItemsBySpecialitiesScholarshipsExperiences(const char* speciality, const char* scholarships, const int start, const int end );
void transTextGroupe(const char* nickname, const char* ptrGroupe, const char* ptrTexte); // groupes possibles: Formation ou Specialite
void transTextPersonnel(const char* nickname1, const char* nickname2, const char* ptrTexte);


void printMember(Member member, int recordIndex);
void printHeader();
void printFooter();
