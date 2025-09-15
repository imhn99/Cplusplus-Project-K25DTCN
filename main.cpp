#include "AccountManager.h"
#include "Wallet.h"
#include "AppCLI.h"

int main(){
    AccountManager accountManager;
    Wallet wallet;
    showAuthMenu(accountManager, wallet);
    return 0;
}