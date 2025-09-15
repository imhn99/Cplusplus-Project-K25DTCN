#include <iostream>
#include <limits>
#include "AccountManager.h"
#include "Wallet.h"

void clearScreen() {
    // Xóa màn hình console
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void showUserMenu(User* currentUser, AccountManager& accountManager, Wallet& wallet) {
    int choice;
    while (true) {
        clearScreen();
        std::cout << "--- Chao mung, " << currentUser->getUsername() << "! ---\n";
        std::cout << "So diem hien tai: " << currentUser->getPoints() << " diem.\n\n";
        std::cout << "1. Xem lich su giao dich\n";
        std::cout << "2. Cong diem (chi co the tu he thong)\n";
        std::cout << "3. Dang xuat\n";
        std::cout << "Nhap lua chon cua ban: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                clearScreen();
                std::cout << "--- Lich su giao dich ---\n";
                auto history = wallet.getTransactions(currentUser->getId());
                if (history.empty()) {
                    std::cout << "Ban chua co giao dich nao.\n";
                } else {
                    for (const auto& t : history) {
                        std::cout << "Loai: " << (t.amount > 0 ? "Cong" : "Tru") 
                                  << ", So diem: " << t.amount 
                                  << ", Noi dung: " << t.description << "\n";
                    }
                }
                std::cout << "\nNhan Enter de tro lai...";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
                break;
            }
            case 2: {
                // Ví d? don gi?n, cho phép ngu?i dùng t? c?ng di?m d? ki?m tra
                int amount;
                std::string description;
                std::cout << "Nhap so diem muon cong: ";
                std::cin >> amount;
                std::cin.ignore();
                std::cout << "Nhap noi dung: ";
                std::getline(std::cin, description);
                
                wallet.addTransaction(currentUser->getId(), amount, description);
                accountManager.updatePoints(currentUser->getId(), currentUser->getPoints() + amount);
                currentUser->setPoints(currentUser->getPoints() + amount); // C?p nh?t ngay trong session
                std::cout << "Da cong " << amount << " diem.\n";
                std::cout << "So diem hien tai: " << currentUser->getPoints() << " diem.\n";
                break;
            }
            case 3:
                return;
            default:
                std::cout << "Lua chon khong hop le. Vui long nhap lai.\n";
                break;
        }
    }
}

void showAuthMenu(AccountManager& accountManager, Wallet& wallet) {
    int choice;
    std::string username, password;
    while (true) {
        clearScreen();
        std::cout << "--- HE THONG QUAN LY DIEM THUONG ---\n";
        std::cout << "1. Dang nhap\n";
        std::cout << "2. Dang ky\n";
        std::cout << "3. Thoat\n";
        std::cout << "Nhap lua chon: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Ten dang nhap: ";
                std::cin >> username;
                std::cout << "Mat khau: ";
                std::cin >> password;
                
                if (User* user = accountManager.login(username, password)) {
                    showUserMenu(user, accountManager, wallet);
                } else {
                    std::cout << "Ten dang nhap hoac mat khau khong dung.\n";
                    std::cout << "Nhan Enter de tiep tuc...";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cin.get();
                }
                break;
            case 2:
                std::cout << "Ten dang nhap: ";
                std::cin >> username;
                std::cout << "Mat khau: ";
                std::cin >> password;

                if (accountManager.registerUser(username, password)) {
                    std::cout << "Dang ky thanh cong!\n";
                } else {
                    std::cout << "Ten dang nhap da ton tai. Vui long chon ten khac.\n";
                }
                std::cout << "Nhan Enter de tiep tuc...";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
                break;
            case 3:
                return;
            default:
                std::cout << "Lua chon khong hop le.\n";
                break;
        }
    }
}

int main() {
    AccountManager accountManager;
    Wallet wallet;

    showAuthMenu(accountManager, wallet);

    return 0;
}
