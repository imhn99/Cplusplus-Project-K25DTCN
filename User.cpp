#include "User.h"
#include <sstream>

User::User(int id, const std::string& username, const std::string& hashedPassword, int points)
    : id(id), username(username), hashedPassword(hashedPassword), points(points) {}

int User::getId() const { return id; }
std::string User::getUsername() const { return username; }
std::string User::getHashedPassword() const { return hashedPassword; }
int User::getPoints() const { return points; }
void User::setPoints(int points) { this->points = points; }

std::string User::toString() const {
    std::stringstream ss;
    ss << id << "|" << username << "|" << hashedPassword << "|" << points;
    return ss.str();
}
