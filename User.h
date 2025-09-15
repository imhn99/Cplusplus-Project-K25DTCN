#ifndef USER_H
#define USER_H

#include <string>

class User {
public:
    User(int id, const std::string& username, const std::string& password, int points = 0);
    int getId() const;
    std::string getUsername() const;
    std::string getPassword() const; // Ch? tr? v? m?t kh?u dã du?c hash
    int getPoints() const;
    void setPoints(int points);
    std::string toString() const;

private:
    int id;
    std::string username;
    std::string password; // M?t kh?u dã du?c hash
    int points;
};

#endif
