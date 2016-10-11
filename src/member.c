#include <stdio.h>
#include <stdlib.h>
#include "member.h"

Member* createMember() {
    Member* member = malloc(sizeof(Member));
    member->experiences = 0;
    return member;
}

void displayMember(Member* member) {
    printf("Experiences : %d\n", member->experiences);
}
