//
// Created by Nicolas Boisvert on 16-11-20.
//

#ifndef SIF1015_USER_H
#define SIF1015_USER_H

typedef struct {
    char* nickname;
    char* speciality;
    char* scholarships;
    int experiences;
} User;

void printUser(User user);
User createUser(char* nickname, char* speciality, char* scholarships, int experiences);

#endif //SIF1015_USER_H
