#ifndef DATABASESERVICE_H
#define DATABASESERVICE_H

#include <sqlite3.h>
#include <string>
#include <filesystem>

class DatabaseService
{
private:
    sqlite3 *db;

public:
    DatabaseService(const std::string &databasePath);
    ~DatabaseService();

    // Operations
    void initializeDatabase();
    void insertRecord(const std::string &fileName,
                      const std::string &transcription,
                      const std::string &tags,
                      const std::string &uploadStatus,
                      const std::string &uploadPath);

    // Other database related operations
};

#endif // DATABASESERVICE_H