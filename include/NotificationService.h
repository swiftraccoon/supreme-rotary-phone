#ifndef NOTIFICATIONSERVICE_H
#define NOTIFICATIONSERVICE_H

#include <librdkafka/rdkafkacpp.h>
#include <string>
#include <memory>

class NotificationService
{
private:
    std::unique_ptr<RdKafka::Producer> producer;
    std::unique_ptr<RdKafka::Conf> conf;
    std::string brokers;
    std::string topicStr;

public:
    NotificationService(const std::string &brokers, const std::string &topic);
    void publishMessage(const std::string &key, const std::string &message);
};

#endif // NOTIFICATIONSERVICE_H