#include <stdlib.h>
#include <stdio.h>
#include "main.h"
#include "linked_list.h"
#include "member.h"
#include "main.h"


int main() {
    Member* member1 = createMember();
    member1->experiences = 2;
    Member* member2 = createMember();
    member2->experiences = 23;
    Member* member3 = createMember();
    member3->experiences = 254;
    Member* member4 = createMember();
    member4->experiences = 1000;
    Member* member5 = createMember();
    member5->experiences = 1123;

    Node* head = createNode(member1);
    appendNode(head, member2);
    appendNode(head, member3);
    appendNode(head, member4);
    printf("\n");
    displayAll(head);
    removeNode(head, member3);
    printf("\n");
    displayAll(head);
    replaceNode(head, member4, member5);
    printf("\n");
    displayAll(head);
    return 0;
}
