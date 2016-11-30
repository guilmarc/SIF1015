#ifndef USER_H
#define USER_H
#include <string>
using namespace std;

class User
{
private:
    string nickname;
    string specialty;
    string scholarships;
    int experiences;
    static User *loggedUser;
public:
    User();
    User(string nickname, string specialty, string scholarships, int experiences);
    string getNickname();
    string getSpecialty();
    string getScholarships();
    int getExperiences();

    void setNickname(string nickname);
    void setSpecialty(string specialty);
    void setScholarships(string scholarships);
    void setExperiences(int experiences);

    string getAddCommand();

    static void logUser(string nickname, string specialty, string scholarships, int experiences);
    static User* getLoggedUser();
};

#endif // USER_H
