#ifndef MEMBER_INFO_H
#define MEMBER_INFO_H

typedef struct {
	/*char nickname[100];
	char speciality[100];
	char scholarships[100];*/
	int experiences;
} MemberInfo;


MemberInfo* createMemberInfo();
void displayMemberInfo(MemberInfo* member);

#endif
