#include <boost/process.hpp>
#include <string>
#include <filesystem>
#include <iostream>
#include <queue>
#include <mutex>
#include <thread>
#include <condition_variable>

namespace bp = boost::process;

class FasterWhisperTranscriptionService
{
private:
    std::queue<std::filesystem::path> jobsQueue;
    std::mutex queueMutex;
    std::condition_variable queueCondition;
    std::atomic<bool> stopSignal{false};
    std::thread workerThread;
    AudioProcessingOrchestrator &orchestrator;

    void worker()
    {
        while (true)
        {
            std::filesystem::path audioFilePath;
            {
                std::unique_lock<std::mutex> lock(queueMutex);
                queueCondition.wait(lock, [this]
                                    { return !jobsQueue.empty() || stopSignal.load(); });
                if (stopSignal.load())
                    break;
                audioFilePath = std::move(jobsQueue.front());
                jobsQueue.pop();
            }
            // Call the Python transcribing function here
            transcribeAudioFile(audioFilePath);
        }
    }

    void transcribeAudioFile(const std::filesystem::path &audioFilePath)
    {
        std::string python_executable = "python3";
        std::string transcribe_script = "../scripts/FasterWhisper.py";

        bp::ipstream out_stream;
        bp::ipstream err_stream;
        std::vector<std::string> args = {transcribe_script, audioFilePath.string()};

        try
        {
            bp::child child_process(python_executable, args, bp::std_out > out_stream, bp::std_err > err_stream);

            std::string output_line;
            std::string transcribed_text;
            while (child_process.running() && std::getline(out_stream, output_line) && !output_line.empty())
            {
                transcribed_text += output_line;
            }

            std::string error_line;
            while (std::getline(err_stream, error_line) && !error_line.empty())
            {
                orchestrator.getLogger()->error("Transcription Error: {}", error_line);
            }

            child_process.wait();
            if (child_process.exit_code() != 0)
            {
                throw std::runtime_error("Transcription process failed");
            }

            orchestrator.processTranscriptionResult(audioFilePath, transcribed_text);
        }
        catch (const std::exception &e)
        {
            orchestrator.getLogger()->error("Transcription Service Exception: {}", e.what());
        }
    }

public:
    explicit FasterWhisperTranscriptionService(AudioProcessingOrchestrator &orch) : orchestrator(orch)
    {
        workerThread = std::thread(&FasterWhisperTranscriptionService::worker, this);
    }

    ~FasterWhisperTranscriptionService()
    {
        stopSignal.store(true);
        queueCondition.notify_one();
        if (workerThread.joinable())
        {
            workerThread.join();
        }
    }

    void enqueueAudioFile(const std::filesystem::path &audioFilePath)
    {
        std::scoped_lock lock(queueMutex);
        jobsQueue.push(audioFilePath);
        queueCondition.notify_one();
    }
};