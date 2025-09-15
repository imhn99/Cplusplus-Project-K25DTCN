// ==================== WalletManager.cpp ====================
#include "WalletManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <random>

static std::map<std::string, std::string> walletIds;
static std::map<std::string, double> wallets;
static double systemWallet = 0;
static std::string systemWalletId;
static std::vector<std::pair<std::string, std::string>> pendingTopups;

std::string generateWalletId() {
    static const std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, chars.size() - 1);
    std::string id;
    for (int i = 0; i < 8; ++i) id += chars[dist(gen)];
    return id;
}

void loadWallets() {
    wallets.clear();
    walletIds.clear();
    systemWallet = 0;
    systemWalletId.clear();
    pendingTopups.clear();
    std::ifstream f("wallets.db");
    if (!f) {
        std::cout << "Khong mo duoc file wallets.db\n";
        return;
    }
    std::string line;
    while (getline(f, line)) {
        std::stringstream ss(line);
        std::string u, wid; double bal;
        if (ss >> u >> wid >> bal) {
            if (u == "_SYSTEM_") {
                systemWalletId = wid;
                systemWallet = bal;
            } else {
                walletIds[u] = wid;
                wallets[u] = bal;
            }
        }
    }
    if (systemWalletId.empty()) {
        systemWalletId = generateWalletId();
        saveWallets();
    }
    // Load pending topups
    std::ifstream ft("topups.db");
    if (!ft) {
        // Không cần báo lỗi nếu chưa có file topups.db
        return;
    }
    while (getline(ft, line)) {
        std::stringstream ss(line);
        std::string u, code;
        ss >> u >> code;
        pendingTopups.push_back({u, code});
    }
}
// Hàm chính thực hiện trừ điểm từ ví tổng và cộng cho user dựa vào mã giao dịch
void transferFromSystemByWalletId(const std::string &bankCode, double amount) {
    bool found = false;
    for (auto it = pendingTopups.begin(); it != pendingTopups.end(); ++it) {
        if (it->second == bankCode) {
            if (systemWallet >= amount) {
                systemWallet -= amount;
                wallets[it->first] += amount;
                std::cout << "Da chuyen " << amount << " diem tu vi tong den user: " << it->first << "\n";
                pendingTopups.erase(it);
                saveWallets();
            } else {
                std::cout << "Vi tong khong du so du.\n";
            }
            found = true;
            break;
        }
    }
    if (!found) {
        std::cout << "Khong tim thay ma giao dich.\n";
    }
}

void saveWallets() {
    std::ofstream f("wallets.db");
    f << "_SYSTEM_ " << systemWalletId << " " << systemWallet << "\n";
    for (const auto &[u, bal] : wallets) {
        if (walletIds[u].empty()) walletIds[u] = generateWalletId();
        f << u << " " << walletIds[u] << " " << bal << "\n";
    }
    // Save pending topups
    std::ofstream ft("topups.db");
    for (const auto &[u, code] : pendingTopups) {
        ft << u << " " << code << "\n";
    }
}

void requestTopup(const std::string &username, const std::string &bankCode) {
    pendingTopups.push_back({username, bankCode});
    saveWallets();
    std::cout << "Yeu cau nap diem da duoc gui, cho admin xac nhan.\n";
}

void processTopup(const std::string &bankCode, double amount) {
    bool found = false;
    for (auto it = pendingTopups.begin(); it != pendingTopups.end(); ++it) {
        if (it->second == bankCode) {
            wallets[it->first] += amount;
            std::cout << "Admin da xac nhan, da cong " << amount << " diem cho user: " << it->first << "\n";
            pendingTopups.erase(it);
            saveWallets();
            found = true;
            break;
        }
    }
    if (!found) {
        std::cout << "Khong tim thay ma giao dich.\n";
    }
}

std::string getWalletId(const std::string &username) {
    if (username == "_SYSTEM_") return systemWalletId;
    if (walletIds.count(username) == 0 || walletIds[username].empty()) {
        walletIds[username] = generateWalletId();
        if (wallets.count(username) == 0) wallets[username] = 0;
        saveWallets();
    }
    return walletIds[username];
}

double getWalletBalance(const std::string &username) {
    return wallets.count(username) ? wallets[username] : 0;
}

void showBalance(const std::string &username) {
    std::cout << "So du cua " << username << ": " << getWalletBalance(username) << ", Ma vi: " << getWalletId(username) << "\n";
}

void showSystemBalance() {
    std::cout << "So du vi tong: " << systemWallet << ", Ma vi tong: " << systemWalletId << "\n";
}

void addToSystemWallet(double amt) {
    systemWallet += amt;
    saveWallets();
    std::cout << "Da nap vao vi tong: " << amt << "\n";
}

void transferFromSystem(const std::string &to, double amt) {
    if (systemWallet >= amt) {
        systemWallet -= amt;
        wallets[to] += amt;
        saveWallets();
        std::cout << "Da chuyen " << amt << " tu vi tong den user: " << to << "\n";
    } else {
        std::cout << "Vi tong khong du so du.\n";
    }
}

void transfer(const std::string &from, const std::string &to, double amt) {
    if (wallets[from] >= amt) {
        wallets[from] -= amt;
        wallets[to] += amt;
        saveWallets();
        std::cout << "Da chuyen " << amt << " tu " << from << " sang " << to << "\n";
    } else {
        std::cout << "Khong du so du de chuyen.\n";
    }
}

void showAllWallets() {
    for (const auto &[u, bal] : wallets) {
        std::cout << "User: " << u << ", Ma vi: " << walletIds[u] << ", So du: " << bal << "\n";
    }
}
