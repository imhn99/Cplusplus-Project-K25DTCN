#ifndef BACKUP_UTIL_H
#define BACKUP_UTIL_H

#include <string>

// Copy tat ca file trong dataDir sang backups/backup_<epoch>
// Tra ve duong dan backup vua tao
std::string createBackup(const std::string& dataDir, const std::string& backupRoot);

#endif

