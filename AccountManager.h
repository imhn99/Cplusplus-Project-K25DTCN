#ifndef ACCOUNT_MANAGER_H
#define ACCOUNT_MANAGER_H

#include "User.h"
#include <vector>

class AccountManager {
public:
    AccountManager();
    User* login(const std::string& username, const std::string& password);
    bool registerUser(const std::string& username, const std::string& password);
    void saveUsers();
    void updatePoints(int userId, int newPoints);
    int getNextUserId();

private:
    std::vector<User> users;
    void loadUsers();
};

#endif
