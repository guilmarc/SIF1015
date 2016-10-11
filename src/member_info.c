#include <stdio.h>
#include <stdlib.h>
#include "member_info.h"

MemberInfo* createMemberInfo() {
    MemberInfo* member = malloc(sizeof(MemberInfo));
    member->experiences = 0;
    return member;
}

void displayMemberInfo(MemberInfo* member) {
    printf("Experiences : %d\n", member->experiences);
}
