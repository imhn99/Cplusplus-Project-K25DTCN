#ifndef OTP_MANAGER_H
#define OTP_MANAGER_H
#include <string>
std::string generateOTP(int = 6);
bool verifyOTP(const std::string &, const std::string &);
#endif