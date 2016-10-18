#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include "member.h"

typedef struct node {
	Member* member;
    struct node* next;
} Node;

Node* getLastNode(Node* headNode);
Node* createNode();
void appendNode(Node* headNode, Member* member);
int removeNode(Node* headNode, Member* member);
int replaceNode(Node* headNode, Member* oldMember, Member* newMember);
int countNodes(Node* headNode);
void displayAll(Node* headNode);

#endif
