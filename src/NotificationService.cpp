#include "NotificationService.h"
#include <iostream>

NotificationService::NotificationService(const std::string &brokers, const std::string &topic)
    : brokers(brokers), topicStr(topic)
{

    std::string errstr;

    // Producer configuration
    conf.reset(RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL));
    if (!conf)
    {
        throw std::runtime_error("Failed to create RdKafka configuration object");
    }

    if (conf->set("metadata.broker.list", brokers, errstr) != RdKafka::Conf::CONF_OK)
    {
        throw std::runtime_error("Failed to set broker list: " + errstr);
    }

    // Create producer instance
    producer.reset(RdKafka::Producer::create(conf.get(), errstr));
    if (!producer)
    {
        throw std::runtime_error("Failed to create producer: " + errstr);
    }
}

void NotificationService::publishMessage(const std::string &key, const std::string &message)
{
    RdKafka::ErrorCode resp = producer->produce(
        topicStr, RdKafka::Topic::PARTITION_UA,
        RdKafka::Producer::RK_MSG_COPY /* Copy payload */,
        const_cast<char *>(message.c_str()), message.size(),
        &key, nullptr);

    if (resp != RdKafka::ERR_NO_ERROR)
    {
        std::cerr << "% Produce failed: " << RdKafka::err2str(resp) << std::endl;
    }
    else
    {
        std::cout << "% Produced message to " << topicStr << std::endl;
    }

    producer->poll(0);
}