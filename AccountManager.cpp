#include "AccountManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip> // D�ng cho setw

// H�m bam mat khau don gian (chi de minh hoa, khong an toan)
std::string hashPassword(const std::string& password) {
    std::hash<std::string> hasher;
    size_t hashed = hasher(password);
    return std::to_string(hashed);
}

AccountManager::AccountManager() {
    loadUsers();
}

AccountManager::~AccountManager() {
    // Kh�ng can saveUsers() v� viec update d� duoc thuc hien ngay
    // khi c� thay doi.
}

void AccountManager::loadUsers() {
    std::ifstream file("data/users.txt");
    if (!file.is_open()) {
        std::cerr << "Khong tim thay file users.txt. Tao moi.\n";
        return;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string id_str, username, hashedPassword, points_str;
        
        std::getline(ss, id_str, '|');
        std::getline(ss, username, '|');
        std::getline(ss, hashedPassword, '|');
        std::getline(ss, points_str, '|');

        int id = std::stoi(id_str);
        int points = std::stoi(points_str);
        
        users.emplace(id, User(id, username, hashedPassword, points));
    }
    file.close();
}

bool AccountManager::registerUser(const std::string& username, const std::string& password) {
    for (const auto& pair : users) {
        if (pair.second.getUsername() == username) {
            return false; // T�n dang nhap d� ton tai
        }
    }
    int newId = getNextUserId();
    std::string hashedPassword = hashPassword(password);
    User newUser(newId, username, hashedPassword);
    users.emplace(newId, newUser);
    
    // Ghi nguoi d�ng moi v�o cuoi file
    std::ofstream file("data/users.txt", std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Khong the mo file users.txt de ghi du lieu.\n";
        return false;
    }
    file << newUser.toString() << "\n";
    file.close();

    return true;
}

User* AccountManager::login(const std::string& username, const std::string& password) {
    std::string hashedPassword = hashPassword(password);
    for (auto& pair : users) {
        if (pair.second.getUsername() == username && pair.second.getHashedPassword() == hashedPassword) {
            return &pair.second;
        }
    }
    return nullptr;
}

void AccountManager::updatePoints(int userId, int newPoints) {
    if (users.count(userId) > 0) {
        users.at(userId).setPoints(newPoints);
        updateUserInFile(userId, newPoints);
    }
}

void AccountManager::updateUserInFile(int userId, int newPoints) {
    // Sua truc tiep diem cua nguoi d�ng trong file
    // C�ch n�y hieu qua hon so voi viec ghi lai toan bo file
    std::ifstream inputFile("data/users.txt");
    std::ofstream outputFile("data/users.tmp", std::ios::trunc);
    std::string line;
    
    if (!inputFile.is_open() || !outputFile.is_open()) {
        std::cerr << "Loi mo file de cap nhat.\n";
        return;
    }
    
    while (std::getline(inputFile, line)) {
        std::stringstream ss(line);
        std::string id_str;
        std::getline(ss, id_str, '|');
        
        if (std::stoi(id_str) == userId) {
            // Cap nhat diem cho d�ng n�y
            User& user = users.at(userId);
            user.setPoints(newPoints);
            outputFile << user.toString() << "\n";
        } else {
            // Giu nguy�n c�c d�ng kh�c
            outputFile << line << "\n";
        }
    }

    inputFile.close();
    outputFile.close();
    
    remove("data/users.txt");
    rename("data/users.tmp", "data/users.txt");
}

int AccountManager::getNextUserId() {
    if (users.empty()) {
        return 1;
    }
    int maxId = 0;
    for(const auto& pair : users) {
        if (pair.first > maxId) {
            maxId = pair.first;
        }
    }
    return maxId + 1;
}
