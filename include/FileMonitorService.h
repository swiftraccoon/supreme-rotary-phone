#ifndef FILEMONITORSERVICE_H
#define FILEMONITORSERVICE_H

#include <string>

/**
 * @class FileMonitorService
 * @brief Monitors a directory for new MP3 files.
 *
 * This service continuously monitors a specified directory for new MP3 files
 * and notifies the orchestrator when a new file is detected.
 */
class FileMonitorService
{
public:
    /**
     * Constructor for FileMonitorService.
     * @param orchestrator Reference to the AudioProcessingOrchestrator.
     * @param directory Path to the directory to be monitored.
     */
    FileMonitorService(AudioProcessingOrchestrator &orchestrator, const std::string &directory);

    // Other public members...

private:
    // Private members and methods...
};

#endif // FILEMONITORSERVICE_H
