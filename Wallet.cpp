#include "Wallet.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <ctime>

Wallet::Wallet() {
    loadTransactions();
}

void Wallet::addTransaction(int userId, int amount, const std::string& description) {
    // Lay thoi gian hien tai
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
    
    Transaction newTransaction = {userId, amount, description, buf};
    transactions.push_back(newTransaction);

    // Ghi giao dich moi vào cuoi file
    std::ofstream file("data/transactions.txt", std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Khong the mo file transactions.txt de ghi du lieu.\n";
        return;
    }
    file << newTransaction.userId << "|" << newTransaction.amount << "|" << newTransaction.description << "|" << newTransaction.timestamp << "\n";
    file.close();
}

std::vector<Transaction> Wallet::getTransactions(int userId) {
    std::vector<Transaction> userTransactions;
    for (const auto& t : transactions) {
        if (t.userId == userId) {
            userTransactions.push_back(t);
        }
    }
    return userTransactions;
}

void Wallet::loadTransactions() {
    std::ifstream file("data/transactions.txt");
    if (!file.is_open()) {
        std::cerr << "Khong tim thay file transactions.txt. Tao moi.\n";
        return;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string userId_str, amount_str, description, timestamp;

        std::getline(ss, userId_str, '|');
        std::getline(ss, amount_str, '|');
        std::getline(ss, description, '|');
        std::getline(ss, timestamp, '|');
        
        int userId = std::stoi(userId_str);
        int amount = std::stoi(amount_str);

        transactions.push_back({userId, amount, description, timestamp});
    }
    file.close();
}
