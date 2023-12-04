#ifndef FASTERWHISPERTRANSCRIPTIONSERVICE_H
#define FASTERWHISPERTRANSCRIPTIONSERVICE_H

#include <string>
#include <queue>
#include <mutex>
#include <thread>

/**
 * @class FasterWhisperTranscriptionService
 * @brief Handles the transcription of audio files.
 *
 * This service manages the transcription of audio files using the Faster Whisper model,
 * maintaining a queue of transcription tasks and processing them asynchronously.
 */
class FasterWhisperTranscriptionService
{
public:
    /**
     * Constructor for FasterWhisperTranscriptionService.
     * @param orchestrator Reference to the AudioProcessingOrchestrator.
     */
    explicit FasterWhisperTranscriptionService(AudioProcessingOrchestrator &orchestrator);

    // Other public members...

private:
    // Private members and methods...
};

#endif // FASTERWHISPERTRANSCRIPTIONSERVICE_H
