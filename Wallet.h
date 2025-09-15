#ifndef WALLET_H
#define WALLET_H

#include <string>
#include <vector>

struct Transaction {
    int userId;
    int amount;
    std::string description;
};

class Wallet {
public:
    Wallet();
    void addTransaction(int userId, int amount, const std::string& description);
    std::vector<Transaction> getTransactions(int userId);

private:
    std::vector<Transaction> transactions;
    void loadTransactions();
    void saveTransactions();
};

#endif
