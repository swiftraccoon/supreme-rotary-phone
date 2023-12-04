#ifndef DATABASESERVICE_H
#define DATABASESERVICE_H

#include <sqlite3.h>
#include <string>
#include <filesystem>

/**
 * @class DatabaseService
 * @brief Service for handling database operations.
 *
 * This service is responsible for managing all interactions with the SQLite database,
 * including initializing the database, inserting records, and other database-related operations.
 */
class DatabaseService
{
private:
    sqlite3 *db; /*!< Pointer to the SQLite database. */

public:
    /**
     * Constructor for DatabaseService.
     * @param databasePath Path to the SQLite database file.
     */
    DatabaseService(const std::string &databasePath);

    /**
     * Destructor for DatabaseService.
     */
    ~DatabaseService();

    /**
     * Initializes the database by creating necessary tables.
     */
    void initializeDatabase();

    /**
     * Inserts a record into the database.
     * @param fileName Name of the file being processed.
     * @param transcription Transcription text of the audio file.
     * @param tags Tags associated with the audio file.
     * @param uploadStatus Status of the file upload.
     * @param uploadPath Path where the file was uploaded.
     */
    void insertRecord(const std::string &fileName,
                      const std::string &transcription,
                      const std::string &tags,
                      const std::string &uploadStatus,
                      const std::string &uploadPath);

    // Other database related operations
};

#endif // DATABASESERVICE_H