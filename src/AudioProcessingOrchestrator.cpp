#include <iostream>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <yaml-cpp/yaml.h>
#include <sqlite3.h>
#include <string>
#include <memory>

#include "../include/UploadService.h"

class AudioProcessingOrchestrator
{
private:
    YAML::Node config;

    // Database Connection
    std::unique_ptr<sqlite3, decltype(&sqlite3_close)> db_connection{nullptr, sqlite3_close};

    // Logging
    std::shared_ptr<spdlog::logger> logger;

    // Configuration file path
    std::string configFilePath;

    // Services
    std::unique_ptr<FileMonitorService> fileMonitorService;
    std::unique_ptr<FasterWhisperTranscriptionService> transcriptionService;
    std::unique_ptr<UploadService> uploadService;
    std::unique_ptr<DatabaseService> databaseService;
    std::unique_ptr<NotificationService> notificationService;

public:
    AudioProcessingOrchestrator(std::string configFile) : configFilePath(std::move(configFile))
    {
        // Load configuration
        try
        {
            config = YAML::LoadFile(configFilePath);
        }
        catch (const YAML::Exception &e)
        {
            std::cerr << "Error loading config file: " << e.what() << std::endl;
            throw;
        }

        // Initialize upload service using configuration
        uploadService = std::make_unique<UploadService>(
            "<minio endpoint>", "<minio access key>", "<minio secret key>", "<bucket name>");

        // Initialize services
        initializeDatabase();
        initializeLogging();
        databaseService = std::make_unique<DatabaseService>(databasePath);
        notificationService = std::make_unique<NotificationService>(brokers, topic);
        // More initializations can be done here
    }

    void initializeLogging()
    {
        try
        {
            auto log_level = spdlog::level::from_str(config["logging"]["level"].as<std::string>());
            auto logger = spdlog::basic_logger_mt("audio_processing_logger", "../logs/audio_processing.log");
            logger->set_formatter(std::make_unique<CustomFormatter>()); // Custom formatter
            logger->set_level(log_level);
            logger->flush_on(log_level);
        }
        catch (const spdlog::spdlog_ex &ex)
        {
            std::cerr << "Logging initialization failed: " << ex.what() << std::endl;
            throw;
        }
    }

    void initializeDatabase()
    {
        const auto dbPath = config["database"]["path"].as<std::string>();
        if (sqlite3_open(dbPath.c_str(), &db_connection.get()) != SQLITE_OK)
        {
            logger->critical("Could not open database: {}", sqlite3_errmsg(db_connection.get()));
            throw std::runtime_error(sqlite3_errmsg(db_connection.get()));
        }

        // Further database initialization and table creation logic goes here
    }

    void startServices()
    {
        transcriptionService = std::make_unique<FasterWhisperTranscriptionService>(*this);
        // Start and initialize other services...
    }

    void stopServices()
    {
        transcriptionService.reset();
        // Clean up other services...
    }

    void processNewFile(const std::filesystem::path &audioFilePath)
    {
        // ...
        transcriptionService->enqueueAudioFile(audioFilePath);
        // ...
    }

    void processTranscriptionResult(const std::filesystem::path &audioFilePath, const std::string &transcription)
    {
        // Process the transcription result (e.g., save it in the database)

        // Instantiate the tagging service and update the MP3 tags with the transcription
        MP3TaggingService taggingService;
        std::map<std::string, std::string> additionalTags; // Customize this as needed
        taggingService.updateTags(audioFilePath.string(), transcription, additionalTags);

        // Proceed with any further processing (e.g., notifying other services)
    }

    void processTaggingResult(const std::filesystem::path &audioFilePath)
    {
        // All processing is complete, upload to MinIO
        std::string destinationPath = "uploads/" + audioFilePath.filename().string();
        uploadService->uploadFile(audioFilePath, destinationPath);

        // Continue with further processing or notifications...
    }

    void finalizeProcessing(const std::filesystem::path &audioFilePath,
                            const std::string &transcription,
                            const std::string &tags,
                            const std::string &uploadStatus,
                            const std::string &uploadPath)
    {
        // Collect and format data, then save to the database
        databaseService->insertRecord(audioFilePath.filename().string(),
                                      transcription,
                                      tags,
                                      uploadStatus,
                                      uploadPath);
        // Further processing or logging...
    }

    void notifyKafka(const std::string &key, const std::string &message)
    {
        notificationService->publishMessage(key, message);
        // You can now send notifications about the processed mp3 file
    }

    void run()
    {
        logger->info("Audio processing orchestrator started.");

        // Retrieve the monitored directory from the configuration
        std::string monitoredDirectory = config["file_monitor"]["directory"].as<std::string>();

        // Initialize File Monitor Service instance
        fileMonitorService = std::make_unique<FileMonitorService>(*this, monitoredDirectory);

        // Start the file monitoring in a separate thread
        std::thread fileMonitorThread(&FileMonitorService::monitor, fileMonitorService.get());

        // Join the file monitor thread (this could be conditional based on a shutdown event in a full implementation)
        fileMonitorThread.join();
    }
};

int main(int argc, char *argv[])
{
    try
    {
        if (argc < 2)
        {
            std::cerr << "Usage: " << argv[0] << " <configuration_path>" << std::endl;
            return 1;
        }

        std::string configFilePath = argv[1];
        AudioProcessingOrchestrator orchestrator(configFilePath);
        orchestrator.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}