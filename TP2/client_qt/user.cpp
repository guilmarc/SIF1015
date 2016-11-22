#include "user.h"

User* User::loggedUser;

User::User()
{
    this->setNickname("");
    this->setSpecialty("");
    this->setScholarships("");
    this->setExperiences(0);
}

User::User(string nickname, string specialty, string scholarships, int experiences)
{
    this->setNickname(nickname);
    this->setSpecialty(specialty);
    this->setScholarships(scholarships);
    this->setExperiences(experiences);
}

string User::getNickname()
{
    return this->nickname;
}

string User::getSpecialty()
{
    return this->specialty;
}

string User::getScholarships()
{
    return this->scholarships;
}

int User::getExperiences()
{
    return this->experiences;
}

void User::setNickname(string nickname)
{
    this->nickname = nickname;
}

void User::setSpecialty(string specialty)
{
    this->specialty = specialty;
}

void User::setScholarships(string scholarships)
{
    this->scholarships = scholarships;
}

void User::setExperiences(int experiences)
{
    this->experiences = experiences;
}

User* User::getLoggedUser()
{
    return User::loggedUser;
}

string User::getAddCommand()
{
    return "A " + this->getNickname() + " " + this->getSpecialty() + " " + this->getScholarships() + " " + to_string(this->getExperiences());
}

void User::logUser(string nickname, string specialty, string scholarships, int experiences)
{
    User::loggedUser = new User(nickname, specialty, scholarships, experiences);
}
