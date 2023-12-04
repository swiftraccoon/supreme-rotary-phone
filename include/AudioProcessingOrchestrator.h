#ifndef AUDIOPROCESSINGORCHESTRATOR_H
#define AUDIOPROCESSINGORCHESTRATOR_H

#include <string>
#include <memory>

/**
 * @class AudioProcessingOrchestrator
 * @brief Orchestrates the audio processing workflow.
 *
 * This class is responsible for coordinating the overall process of monitoring,
 * transcribing, tagging, uploading, and notifying for MP3 files.
 */
class AudioProcessingOrchestrator
{
public:
    /**
     * Constructor for AudioProcessingOrchestrator.
     * @param configFile Path to the configuration file.
     */
    explicit AudioProcessingOrchestrator(const std::string &configFile);

    // Other public members...

private:
    // Private members and methods...
};

#endif // AUDIOPROCESSINGORCHESTRATOR_H
