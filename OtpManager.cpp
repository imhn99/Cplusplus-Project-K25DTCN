#include "OtpManager.h"
#include <random>
std::string generateOTP(int len){static const std::string d="0123456789";std::random_device rd;std::mt19937 g(rd());std::uniform_int_distribution<>dis(0,d.size()-1);std::string r;for(int i=0;i<len;++i)r+=d[dis(g)];return r;}
bool verifyOTP(const std::string &g,const std::string &i){return g==i;}