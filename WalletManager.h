// ==================== WalletManager.h ====================
#ifndef WALLET_MANAGER_H
#define WALLET_MANAGER_H
#include <string>
void loadWallets();
void saveWallets();
void showBalance(const std::string &);
void showSystemBalance();
void addToSystemWallet(double);
void transferFromSystem(const std::string &, double);
void transfer(const std::string &, const std::string &, double);
void showAllWallets();
double getWalletBalance(const std::string &);
std::string getWalletId(const std::string &);
#endif