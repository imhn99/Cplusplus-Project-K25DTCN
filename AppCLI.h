
#ifndef APP_CLI_H
#define APP_CLI_H

#include <string>

// Forward declarations
class AccountManager;
class User;
class Wallet;

void showUserMenu(User* currentUser, AccountManager& accountManager, Wallet& wallet);
void showAuthMenu(AccountManager& accountManager, Wallet& wallet);

#endif