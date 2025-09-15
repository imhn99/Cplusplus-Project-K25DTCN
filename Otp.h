#ifndef OTP_H
#define OTP_H

#include <string>
#include <unordered_map>
#include <ctime>

class Otp {
public:
    // Tao OTP 6 so, het han sau ttlSec (mac dinh 120s)
    std::string issue(const std::string& username, int ttlSec = 120);
    bool verify(const std::string& username, const std::string& code);

private:
    struct Item { std::string code; std::time_t expiresAt; };
    std::unordered_map<std::string, Item> store;
};

#endif

