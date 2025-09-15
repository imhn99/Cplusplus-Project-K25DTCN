// ==================== main.cpp ====================
#include <iostream>
#include "UserManager.h"
#include "WalletManager.h"
#include "OtpManager.h"

// Declare the missing function to fix the undefined identifier error
void requestTopup(const std::string& username, const std::string& code);

void userMenu(const std::string &username);
void adminMenu(const std::string &username);
// Declare the missing function to fix the undefined identifier error
void transferFromSystemByWalletId(const std::string& code, double amt);

int main() {
    loadUsers();
    loadWallets();

    while (true) {
        std::string uname;
        int firstChoice;
        std::cout << "1. Dang nhap\n2. Dang ky\n3. Thoat\nChon: ";
        std::cin >> firstChoice; std::cin.ignore();

        if (firstChoice == 1) uname = loginUser();
        else if (firstChoice == 2) uname = registerUser();
        else if (firstChoice == 3) {
            std::cout << "Thoat chuong trinh...\n";
            break;
        }
        else {
            std::cout << "Lua chon khong hop le.\n";
            continue;
        }

        if (uname.empty()) continue;

        if (getUserRole(uname) == "admin") {
            adminMenu(uname);
        } else {
            userMenu(uname);
        }
    }

    saveUsers();
    saveWallets();
    return 0;
}

void userMenu(const std::string &username) {
    int choice;
    do {
        std::cout << "1. Xem thong tin\n2. Xem so du\n3. Chuyen diem (OTP)\n4. Doi mat khau (OTP)\n5. Doi thong tin (OTP)\n6. Nap diem (OTP + ma giao dich)\n7. Dang xuat\nChon: ";
        std::cin >> choice; std::cin.ignore();
        if (choice == 1) showUserInfo(username);
        else if (choice == 2) showBalance(username);
        else if (choice == 3) {
            std::string otp = generateOTP();
            std::cout << "OTP cua ban: " << otp << "\n";
            std::string inputOtp;
            std::cout << "Nhap OTP: "; std::cin >> inputOtp;
            if (verifyOTP(otp, inputOtp)) {
                std::string to; double amt;
                std::cout << "To: "; std::cin >> to;
                std::cout << "So diem: "; std::cin >> amt;
                transfer(username, to, amt);
            } else std::cout << "OTP sai.\n";
        }
        else if (choice == 4) {
            std::string otp = generateOTP();
            std::cout << "OTP cua ban: " << otp << "\n";
            std::string inputOtp;
            std::cout << "Nhap OTP: "; std::cin >> inputOtp;
            if (verifyOTP(otp, inputOtp)) changePassword(username);
            else std::cout << "OTP sai.\n";
        }
        else if (choice == 5) {
            std::string otp = generateOTP();
            std::cout << "OTP cua ban: " << otp << "\n";
            std::string inputOtp;
            std::cout << "Nhap OTP: "; std::cin >> inputOtp;
            if (verifyOTP(otp, inputOtp)) updateUserInfo(username);
            else std::cout << "OTP sai.\n";
        }
        else if (choice == 6) {
            std::string otp = generateOTP();
            std::cout << "OTP cua ban: " << otp << "\n";
            std::string inputOtp;
            std::cout << "Nhap OTP: "; std::cin >> inputOtp;
            if (verifyOTP(otp, inputOtp)) {
                std::string code;
                std::cout << "Nhap ma giao dich ngan hang: ";
                std::cin >> code;
                requestTopup(username, code);
            } else std::cout << "OTP sai.\n";
        }
        else if (choice == 7) {
            std::cout << "Dang xuat...\n";
            break;
        }
        else {
            std::cout << "Lua chon khong hop le.\n";
        }
    } while (true);
}

void adminMenu(const std::string &username) {
    int choice;
    do {
        std::cout << "1. Xem thong tin tat ca thanh vien\n2. Xem vi tong\n3. Nap diem vi tong\n4. Nap diem cho thanh vien (xac nhan ma giao dich va lay tu vi tong)\n5. Dang xuat\nChon: ";
        std::cin >> choice; std::cin.ignore();
        if (choice == 1) showAllUserInfo();
        else if (choice == 2) showSystemBalance();
        else if (choice == 3) {
            double amt;
            std::cout << "So diem muon nap vao vi tong: ";
            std::cin >> amt;
            addToSystemWallet(amt);
        }
        else if (choice == 4) {
            std::string code;
            double amt;
            std::cout << "Nhap ma giao dich: ";
            std::cin >> code;
            std::cout << "So diem quy doi: ";
            std::cin >> amt;
            transferFromSystemByWalletId(code, amt);
        }
        else if (choice == 5) {
            std::cout << "Dang xuat...\n";
            break;
        }
        else {
            std::cout << "Lua chon khong hop le.\n";
        }
    } while (true);
}
