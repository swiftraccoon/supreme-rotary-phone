#include <sys/inotify.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <filesystem>

class FileMonitorService
{
private:
    int inotifyFd;
    int watchDescriptor;
    AudioProcessingOrchestrator &orchestrator;

public:
    FileMonitorService(AudioProcessingOrchestrator &orch, const std::string &directory)
        : orchestrator(orch), inotifyFd(-1), watchDescriptor(-1)
    {
        // Initialize inotify
        inotifyFd = inotify_init();
        if (inotifyFd == -1)
        {
            throw std::runtime_error("inotify_init failed");
        }

        // Add a watch on the directory
        watchDescriptor = inotify_add_watch(inotifyFd, directory.c_str(), IN_CLOSE_WRITE);
        if (watchDescriptor == -1)
        {
            close(inotifyFd);
            throw std::runtime_error("inotify_add_watch failed");
        }
    }

    ~FileMonitorService()
    {
        if (watchDescriptor != -1)
        {
            inotify_rm_watch(inotifyFd, watchDescriptor);
        }
        if (inotifyFd != -1)
        {
            close(inotifyFd);
        }
    }

    // Non-copyable and non-movable
    FileMonitorService(const FileMonitorService &) = delete;
    FileMonitorService &operator=(const FileMonitorService &) = delete;

    // Main loop to monitor
    void monitor()
    {
        try
        {
            constexpr size_t eventSize = sizeof(inotify_event);
            constexpr size_t bufSize = 1024 * (eventSize + NAME_MAX + 1);
            char buffer[bufSize];

            while (true)
            {
                // Read events
                ssize_t length = read(inotifyFd, buffer, bufSize);
                if (length == -1 && errno != EAGAIN)
                {
                    throw std::runtime_error("read error on inotify fd");
                }

                // Process events
                for (char *ptr = buffer; ptr < buffer + length;)
                {
                    auto *event = reinterpret_cast<inotify_event *>(ptr);

                    // Check for 'IN_CLOSE_WRITE' event to avoid partially written files
                    if ((event->mask & IN_CLOSE_WRITE) && std::filesystem::path(event->name).extension() == ".mp3")
                    {
                        orchestrator.processNewFile(std::filesystem::path(event->name));
                    }

                    // Advance to the next event
                    ptr += eventSize + event->len;
                }
            }
        }
        catch (const std::exception &e)
        {
            orchestrator.getLogger()->error("File monitoring error: {}", e.what());
            throw;
        }
    }
};