#include "Otp.h"
#include <random>

static std::string gen6(){
    static std::mt19937 rng((unsigned)std::random_device{}());
    std::uniform_int_distribution<int> d(0,9);
    std::string s; s.reserve(6);
    for(int i=0;i<6;i++) s.push_back(char('0'+d(rng)));
    return s;
}

std::string Otp::issue(const std::string& username, int ttlSec){
    std::string code = gen6();
    store[username] = {code, std::time(nullptr) + ttlSec};
    return code;
}

bool Otp::verify(const std::string& username, const std::string& code){
    auto it = store.find(username);
    if(it == store.end()) return false;
    if(std::time(nullptr) > it->second.expiresAt) return false;
    return it->second.code == code;
}