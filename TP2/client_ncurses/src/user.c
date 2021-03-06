//
// Created by Nicolas Boisvert on 16-11-20.
//

#include "user.h"
#include <stdio.h>
#include <stdlib.h>

void printUser(User user) {
    printf("Nickname : %s\nSpeciality : %s\nSchoolarship : %s\nExperiences : %i", user.nickname, user.speciality, user.scholarships, user.experiences);
}

User createUser(char* nickname, char* speciality, char* scholarships, int experiences) {
    User user;
    user.nickname = nickname;
    user.speciality = speciality;
    user.scholarships = scholarships;
    user.experiences = experiences;
    return user;
}

void userAddCommand(User user, char* refString) {
    char* template = "A %s %s %s %i";
    sprintf(refString, template, user.nickname, user.speciality, user.scholarships, user.experiences);
}