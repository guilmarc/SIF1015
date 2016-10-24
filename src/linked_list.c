#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"


Node* createNode() {
    Node* node = malloc(sizeof(Node));
    node->member = NULL;
    node->next = NULL;
    return node;
}

void appendNode(Node* headNode, Member* member) {
    Node* node = createNode();
    node->member = member;
    Node* lastNode = getLastNode(headNode);
    lastNode->next = node;
}

int removeNode(Node* headNode, Member* member) {
    Node* current = headNode->next;
    Node* previous = headNode;
    while(current != NULL) {
        if(current->member == member) {
            previous->next = current->next;
            free(current);
            return 1;
        }
        previous = previous->next;
        current = current->next;
    }
    return 0;
}

int replaceNode(Node* headNode, Member* oldMember, Member* newMember) {
    Node* current = headNode;
    while(current != NULL) {
        if(current->member == oldMember) {
            current->member = newMember;
            return 1;
        }
        current = current->next;
    }
    return 0;
}

Node* getLastNode(Node* headNode) {
    Node* current = headNode;
    while(current->next != NULL) {
        current = current->next;
    }
    return current;
}

int countNodes(Node* headNode) {
    int count = 0;
    if(headNode != NULL) {
        Node* current = headNode;
        while(current != NULL) {
            count++;
            current = current->next;
        }
    }
    return count;
}

void displayAll(Node* headNode) {
    Node* current = headNode;
    while(current != NULL) {
        displayMember(current->member);
        current = current->next;
    }
}
