#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include "member_info.h"

typedef struct node {
	MemberInfo* member;
    struct node* next;
} Node;

Node* getLastNode(Node* headNode);
Node* createNode(MemberInfo* member);
void appendNode(Node* headNode, MemberInfo* member);
int removeNode(Node* headNode, MemberInfo* member);
int replaceNode(Node* headNode, MemberInfo* oldMember, MemberInfo* newMember);
int countNodes(Node* headNode);
void displayAll(Node* headNode);

#endif
