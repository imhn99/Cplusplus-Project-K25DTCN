#include "BackupUtil.h"
#include <filesystem>
#include <chrono>
#include <sstream>

namespace fs = std::filesystem;

std::string createBackup(const std::string& dataDir, const std::string& backupRoot){
    auto epoch = std::chrono::system_clock::now().time_since_epoch();
    auto secs = std::chrono::duration_cast<std::chrono::seconds>(epoch).count();
    std::stringstream ss;
    ss << backupRoot << "/backup_" << secs;
    std::string dest = ss.str();
    fs::create_directories(dest);
    if(fs::exists(dataDir)){
        for(auto& p : fs::directory_iterator(dataDir)){
            if(fs::is_regular_file(p.path())){
                fs::copy_file(p.path(), fs::path(dest) / p.path().filename(),
                              fs::copy_options::overwrite_existing);
            }
        }
    }
    return dest;
}

