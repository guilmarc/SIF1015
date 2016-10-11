#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include "member_info.h"

typedef struct node {
	MemberInfo member;
    struct node* next;
} Node;

#endif
