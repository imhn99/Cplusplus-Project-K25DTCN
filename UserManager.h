// ==================== UserManager.h ====================
#ifndef USERMANAGER_H
#define USERMANAGER_H
#include <string>
struct UserAccount {
    std::string username, passwordHash, email, role;
    UserAccount() {}
    UserAccount(std::string u, std::string p, std::string e, std::string r) : username(u), passwordHash(p), email(e), role(r) {}
};
void loadUsers();
void saveUsers();
std::string registerUser();
std::string loginUser();
void changePassword(const std::string &);
void updateUserInfo(const std::string &);
void showUserInfo(const std::string &);
void showAllUserInfo();
std::string getUserRole(const std::string &);
#endif