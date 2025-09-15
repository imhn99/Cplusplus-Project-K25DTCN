#include <iostream>
#include <limits>
#include <string>
#include <cstdlib>
#include "AppCLI.h"

// Teammate headers
#include "AccountManager.h"
#include "Wallet.h"
#include "User.h"

// Your extras
#include "Otp.h"
#include "BackupUtil.h"

static void pauseLine(){
    std::cout << "Nhan Enter de tiep tuc...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

static void clearScr(){
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void showUserMenu(User* currentUser, AccountManager& accountManager, Wallet& wallet){
    Otp otp;
    while(true){
        clearScr();
        std::cout << "=== Xin chao, " << currentUser->getUsername() << " ===\n";
        std::cout << "Diem: " << currentUser->getPoints() << "\n";
        std::cout << "1) Nap diem\n";
        std::cout << "2) Tieu diem (yeu cau OTP)\n";
        std::cout << "3) Lich su giao dich\n";
        std::cout << "4) Backup du lieu\n";
        std::cout << "9) Dang xuat\n";
        std::cout << "Chon: ";
        int c; if(!(std::cin>>c)) return;
        if(c==9) return;

        if(c==1){
            int amt; std::cout << "Nhap so diem nap: "; std::cin >> amt;
            if(amt>0){
                int newPts = currentUser->getPoints() + amt;
                accountManager.updatePoints(currentUser->getId(), newPts);
                currentUser->setPoints(newPts); // dong bo view
                wallet.addTransaction(currentUser->getId(), amt, "Nap diem");
                std::cout << "Nap OK.\n";
            } else std::cout << "So khong hop le.\n";
            pauseLine();
        } else if(c==2){
            int amt; std::cout << "Nhap so diem tieu: "; std::cin >> amt;
            if(amt<=0 || currentUser->getPoints() < amt){
                std::cout << "Khong du diem/so khong hop le.\n"; pauseLine(); continue;
            }
            // OTP
            std::string code = otp.issue(currentUser->getUsername(), 120);
            std::cout << "(OTP demo): " << code << "\n";
            std::cout << "Nhap OTP: ";
            std::string input; std::cin >> input;
            if(otp.verify(currentUser->getUsername(), input)){
                int newPts = currentUser->getPoints() - amt;
                accountManager.updatePoints(currentUser->getId(), newPts);
                currentUser->setPoints(newPts);
                wallet.addTransaction(currentUser->getId(), -amt, "Tieu diem");
                std::cout << "Da tru diem.\n";
            } else {
                std::cout << "OTP sai/het han.\n";
            }
            pauseLine();
        } else if(c==3){
            auto txs = wallet.getTransactions(currentUser->getId());
            std::cout << "== Lich su ==\n";
            for(const auto& t : txs){
                // In an toan cho ca 2 ban Wallet.h (co/khong co timestamp)
                std::cout << (t.amount>=0?"+":"") << t.amount << " | " << t.description << "\n";
            }
            pauseLine();
        } else if(c==4){
            std::string path = createBackup("data", "backups");
            std::cout << "Da tao backup: " << path << "\n";
            pauseLine();
        } else {
            std::cout << "Lua chon khong hop le.\n"; pauseLine();
        }
    }
}

void showAuthMenu(AccountManager& accountManager, Wallet& wallet){
    while(true){
        clearScr();
        std::cout << "=== MENU ===\n";
        std::cout << "1) Dang nhap\n";
        std::cout << "2) Dang ky\n";
        std::cout << "0) Thoat\n";
        std::cout << "Chon: ";
        int c; if(!(std::cin>>c)) return;
        if(c==0) return;

        if(c==1){
            std::string u,p;
            std::cout << "Ten dang nhap: "; std::cin >> u;
            std::cout << "Mat khau: "; std::cin >> p;
            if(User* cur = accountManager.login(u,p)){
                showUserMenu(cur, accountManager, wallet);
            } else {
                std::cout << "Sai thong tin dang nhap.\n"; pauseLine();
            }
        } else if(c==2){
            std::string u,p;
            std::cout << "Ten dang nhap: "; std::cin >> u;
            std::cout << "Mat khau: "; std::cin >> p;
            if(accountManager.registerUser(u,p)){
                std::cout << "Dang ky thanh cong.\n";
            } else {
                std::cout << "Ten dang nhap da ton tai.\n";
            }
            pauseLine();
        } else {
            std::cout << "Lua chon khong hop le.\n"; pauseLine();
        }
    }
}
