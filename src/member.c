#include <stdio.h>
#include <stdlib.h>
#include "member.h"
#include <string.h>

Member* createMember() {
    Member* member = malloc(sizeof(Member));
    member->experiences = 0;
    strcpy(member->nickname, "");
    strcpy(member->speciality, "");
    strcpy(member->scholarships, "");
    return member;
}

void displayMember(Member* member) {
    printf("Experiences : %d\n", member->experiences);
}
