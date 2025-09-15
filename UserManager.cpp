// ==================== UserManager.cpp ====================
#include "UserManager.h"
#include "WalletManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <termios.h>
#include <unistd.h>
// #include <conio.h>
static std::map<std::string, UserAccount> users;

void loadUsers() {
    users.clear();
    std::ifstream f("users.db");
    if (!f) {
        std::cout << "Khong mo duoc file users.db.\n";
        return;
    }
    std::string line;
    while (getline(f, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string u, p, e, r;
        if (getline(ss, u, ',') && getline(ss, p, ',') && getline(ss, e, ',') && getline(ss, r, ',')) {
            users[u] = UserAccount(u, p, e, r);
        } else {
            std::cout << "Dong bi loi: " << line << "\n";
        }
    }
}

void saveUsers() {
    std::ofstream f("users.db");
    for (const auto &[u, acc] : users) {
        f << acc.username << "," << acc.passwordHash << "," << acc.email << "," << acc.role << "\n";
    }
}

std::string hashPassword(const std::string &p) {
    std::hash<std::string> h;
    std::ostringstream oss;
    oss << std::hex << h(p);
    return oss.str();
}

// std::string getHiddenPassword() {
//     std::string p;
//     char c;
//     while ((c = getch()) != '\r') {
//         if (c == '\b') {
//             if (!p.empty()) {
//                 p.pop_back();
//                 std::cout << "\b \b";
//             }
//         } else {
//             p += c;
//             std::cout << '*';
//         }
//     }
//     std::cout << "\n";
//     return p;
// }

std::string getHiddenPassword() {
    std::string p;
    char c;
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    while (true) {
        c = getchar();
        if (c == '\n' || c == '\r') break;
        if (c == 127 || c == '\b') { // Xử lý phím backspace
            if (!p.empty()) {
                p.pop_back();
                std::cout << "\b \b";
            }
        } else {
            p += c;
            std::cout << '*';
        }
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    std::cout << "\n";
    return p;
}

std::string registerUser() {
    std::string u, e, p;
    std::cout << "Ten dang nhap: "; getline(std::cin, u);
    if (users.count(u)) {
        std::cout << "Ten dang nhap da ton tai!\n";
        return "";
    }
    std::cout << "Email: "; getline(std::cin, e);
    for (const auto& [_, acc] : users) {
        if (acc.email == e) {
            std::cout << "Email da duoc su dung!\n";
            return "";
        }
    }
    std::cout << "Mat khau (bo trong de tu sinh): "; p = getHiddenPassword();
    if (p.empty()) p = "123456";
    std::string r = users.empty() ? "admin" : "user";
    users[u] = UserAccount(u, hashPassword(p), e, r);
    saveUsers();
    return u;
}

std::string loginUser() {
    std::string u, p;
    std::cout << "Ten dang nhap: "; getline(std::cin, u);
    std::cout << "Mat khau: "; p = getHiddenPassword();
    auto it = users.find(u);
    if (it != users.end() && it->second.passwordHash == hashPassword(p)) {
        return u;
    }
    return "";
}

void changePassword(const std::string &u) {
    std::cout << "Mat khau moi: ";
    std::string p = getHiddenPassword();
    users[u].passwordHash = hashPassword(p);
    saveUsers();
}

void updateUserInfo(const std::string &u) {
    std::cout << "Email moi: ";
    std::string e; getline(std::cin, e);
    users[u].email = e;
    saveUsers();
}

void showUserInfo(const std::string &u) {
    if (users.count(u)) {
        const auto &acc = users[u];
        std::cout << "User: " << acc.username << ", Email: " << acc.email << ", Role: " << acc.role << "\n";
    }
}

void showAllUserInfo() {
    loadUsers();
    if (users.empty()) {
        std::cout << "Khong co thanh vien nao trong he thong hoac file bi trong.\n";
        return;
    }
    std::cout << "=== Danh sach thanh vien ===\n";
    for (const auto &[u, acc] : users) {
        double bal = getWalletBalance(u);
        std::string wid = getWalletId(u);
        std::cout << "User: " << acc.username << ", Email: " << acc.email << ", Role: " << acc.role << ", So du: " << bal << ", Ma vi: " << wid << "\n";
    }
}

std::string getUserRole(const std::string &u) {
    return users[u].role;
}
