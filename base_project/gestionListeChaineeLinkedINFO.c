#include "gestionListeChaineeLinkedINFO.h"


extern Node* head;
extern Node* queue;

Node * findPrev(const char* nickname) {
    if ((head != NULL) || (queue != NULL)) {
        Node * current = head;
        while (current->next != NULL) {

            printf("\n dans findPrev  nick suivant %s NICK %s COMPARAISON %d %d",
                current->next->member.nickname,nickname,
                (int)(strlen(current->next->member.nickname)),
                (int)(strlen(nickname))
            );
            if ((strcmp(current->next->member.nickname, nickname) == 0) ) {
                return current;
            }

            current = current->next;
        }
    }
    return NULL;
}

void addMemberItem(const Member member) {

    Node* node = (Node*)malloc(sizeof(Node));

    node->member = member;

    if (head == NULL) {
        node->next = NULL;
        queue = head = node;
    } else {
        Node* tempNode = queue;
        node->next = NULL;
        queue = node;
        tempNode->next = node;
    }
}

void addItem(const char* nickname, const char* speciality, const char* scholarships, const int experiences) {

    Node* node = (Node*)malloc(sizeof(Node));

    strcpy(node->member.nickname, nickname);
    strcpy(node->member.speciality, speciality);
    strcpy(node->member.scholarships, scholarships);
    node->member.experiences = experiences;

    if (head == NULL) {
        node->next = NULL;
        queue = head = node;
    } else {
        Node* tempNode = queue;
        node->next = NULL;
        queue = node;
        tempNode->next = node;
    }
}

void modifyMemberItem(const int nodeIndex, const Member member) {
    int recordIndex = 1;

    if ((nodeIndex >= 1) && ((head != NULL) || (queue != NULL))) {

        Node * node = head;

        while (node != NULL) {
            if (recordIndex == nodeIndex) {
                node->member = member;
                return;
            } else{
                node = node->next;
                recordIndex++;
            }
        }
    }
}

void modifyItem(const int nodeIndex, const char* nickname, const char* speciality, const char* scholarships, const int experiences) {
    int recordIndex=1;

    if ((nodeIndex >= 1) && ((head != NULL) || (queue != NULL))) {

        Node * node = head;

        while (node != NULL) {
            if (recordIndex == nodeIndex) {
                strcpy(node->member.nickname, nickname);
                strcpy(node->member.speciality, speciality);
                strcpy(node->member.scholarships, scholarships);
                node->member.experiences = experiences;
                //printf("%d: %s \t  %s \t %s \t %s \t %d\n",recordIndex,node->member.nickname,node->member.scholarships, node->member.speciality, node->member.experiences );
                return;
            } else{
                node = node->next;
                recordIndex++;
            }
        }
    }
}

void removeItem(const char* nickname) {
    if ((head != NULL) || (queue != NULL)) {
        Node * node;
        Node * otherNode;
        if (strcmp(head->member.nickname, nickname) == 0) {

            node = head;

            if (head == node) {
                if (head == queue) {
                    free(node);
                    queue = head = NULL;
                    return;
                }
                head = node->next;
                free(node);
            }
        } else {
            node = findPrev(nickname);

            if (node != NULL) {
                if (queue == node->next) {
                    queue = node;
                    free(node->next);
                    node->next = NULL;
                    return;
                } else {
                    otherNode = node->next;
                    node->next = node->next->next;
                    free(otherNode);
                }
            }
        }
    }
}


void listAllItems(const int start, const int end) {
    int recordIndex = 1;
    Node * node = head;

    printHeader();
    while (node != NULL) {

        if ((recordIndex >= start) && (recordIndex <= end)) {
            printMember(node->member, recordIndex);
        }

        if (recordIndex > end) {
            node = NULL;
        } else{
            node = node->next;
            recordIndex++;
        }

    }
    printFooter();
}

void listItemsBySpecialities(const char* speciality) {
    int recordIndex = 1;
    printHeader();

    Node * node = head;

    while (node != NULL) {
        if ((strcmp(node->member.speciality,speciality) == 0)) {
            printMember(node->member, recordIndex);
        } else {
            node = node->next;
            recordIndex++;
        }

    }
    printFooter();
}

void listItemsBySpecialitiesExperiences(const char* speciality, const int start, const int end) {
    int recordIndex = 1;
    Node * node = head;

    printHeader();
    while (node != NULL) {
        if ((strcmp(node->member.speciality,speciality) == 0) && ((node->member.experiences >= start) && (node->member.experiences <= end))) {
            printMember(node->member, recordIndex);
        } else{
            node = node->next;
            recordIndex++;
        }

    }
    printFooter();
}

void listItemsBySpecialitiesScholarships(const char* speciality, const char* scholarships) {
    int recordIndex = 1;
    Node * node = head;

    printHeader();
    while (node != NULL) {
        if ((strcmp(node->member.speciality,speciality) == 0) && (strcmp(node->member.scholarships,scholarships) == 0)) {
            printMember(node->member, recordIndex);
        } else {
            node = node->next;
            recordIndex++;
        }

    }
    printFooter();
}

void listItemsBySpecialitiesScholarshipsExperiences(const char* speciality, const char* scholarships, const int start, const int end ) {
    int recordIndex = 1;
    Node * node = head;

    printHeader();
    while (node != NULL) {
        if ((strcmp(node->member.speciality,speciality) == 0) && (strcmp(node->member.scholarships,scholarships) == 0) && ((node->member.experiences >= start) && (node->member.experiences <= end))) {
            printMember(node->member, recordIndex);
        } else {
            node = node->next;
            recordIndex++;
        }

    }
    printFooter();
}

void transTextGroupe(const char* nickname, const char* group, const char* text) {
    Node * node = head;

    printf("%s \t %s ",nickname, group);
    printf("TEXTE ENVOYE: %s\n",text);

    while (node != NULL) {
        if ((strcmp(node->member.nickname,nickname) != 0) && ((strcmp(node->member.speciality, group) == 0) || (strcmp(node->member.scholarships, group) == 0))) {
            printf("member: %s \t transmet au groupe: %s",node->member.nickname, node->member.speciality);
            printf("\tTEXTE ENVOYE/RECU: %s\n",text);
        }
        node = node->next;
    }
}

void transTextPersonnel(const char* sender, const char* receiver, const char* sentText) {
    Node * node = head;

    printf("%s \t %s ",sender, receiver);
    printf("TEXTE ENVOYE: %s\n", sentText);

    while (node != NULL) {
        if ((strcmp(node->member.nickname, sender) != 0) && (strcmp(node->member.nickname, receiver) == 0)) {
            printf(" member: %s \t transmet au member: %s ", sender, receiver);
            printf("\tTEXTE ENVOYE/RECU: %s\n", sentText);
        }
        node = node->next;
    }
}

void printMember(Member member, int recordIndex) {
    printf("%d: %s \t\t  %s \t\t %s \t\t  %d\n",
        recordIndex,
        member.nickname, member.speciality,
        member.scholarships, member.experiences
    );
}

void printHeader() {
    printf("\n======================================================\n");
    printf("Nickname\t\tSpecialities\t\tScholarships\t\tExperiences\n");
    printf("======================================================\n");
}

void printFooter() {
    printf("======================================================\n\n");
}
