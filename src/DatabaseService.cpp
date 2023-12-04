#include "../include/DatabaseService.h"

DatabaseService::DatabaseService(const std::string &databasePath) : db(nullptr)
{
    try
    {
        if (sqlite3_open(databasePath.c_str(), &db) != SQLITE_OK)
        {
            throw std::runtime_error("Unable to open database: " + std::string(sqlite3_errmsg(db)));
        }
        initializeDatabase();
    }
    catch (const std::exception &e)
    {
        spdlog::error("DatabaseService initialization failed: {}", e.what());
        throw; // Rethrow to handle it at a higher level
    }
}

DatabaseService::~DatabaseService()
{
    sqlite3_close(db);
}

void DatabaseService::initializeDatabase()
{
    const char *sqlCreateTable = R"(
        CREATE TABLE IF NOT EXISTS FileInfo (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            file_name TEXT NOT NULL,
            transcription TEXT,
            tags TEXT,
            upload_status TEXT,
            upload_path TEXT
        );
    )";

    char *errMsg = nullptr;
    if (sqlite3_exec(db, sqlCreateTable, nullptr, nullptr, &errMsg) != SQLITE_OK)
    {
        std::string error = errMsg ? std::string(errMsg) : "Unknown error";
        sqlite3_free(errMsg);
        throw std::runtime_error("SQL error: " + error);
    }
}

void DatabaseService::insertRecord(const std::string &fileName,
                                   const std::string &transcription,
                                   const std::string &tags,
                                   const std::string &uploadStatus,
                                   const std::string &uploadPath)
{
    const char *sqlInsert = R"(
        INSERT INTO FileInfo (file_name, transcription, tags, upload_status, upload_path) 
        VALUES (?, ?, ?, ?, ?);
    )";

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sqlInsert, -1, &stmt, nullptr) != SQLITE_OK)
    {
        throw std::runtime_error("Could not prepare statement");
    }

    // Bind parameters
    sqlite3_bind_text(stmt, 1, fileName.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, transcription.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, tags.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, uploadStatus.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, uploadPath.c_str(), -1, SQLITE_STATIC);

    // Execute statement
    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        sqlite3_finalize(stmt);
        throw std::runtime_error("Could not insert data");
    }

    sqlite3_finalize(stmt);
}

// Implement other methods as needed...