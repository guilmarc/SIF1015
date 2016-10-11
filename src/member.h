#ifndef member_H
#define member_H

typedef struct {
	/*char nickname[100];
	char speciality[100];
	char scholarships[100];*/
	int experiences;
} Member;


Member* createMember();
void displayMember(Member* member);

#endif
