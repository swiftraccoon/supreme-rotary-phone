# Notification Service

## Overview
The Notification Service handles sending notifications to Apache Kafka about the processing status of MP3 files.

## Features
- Sends notifications to Apache Kafka.
- Configurable Kafka topic and broker settings.

## Setup and Configuration
- Requires `librdkafka`.
- Configure Kafka broker and topic details in the main configuration file.

## Usage
This service is used by the Audio Processing Orchestrator to send notifications after each significant processing step.

## Dependencies
- `librdkafka`

## Troubleshooting
- Ensure Kafka brokers are accessible and the specified topic exists.
- Check for network-related issues if Kafka is not reachable.
