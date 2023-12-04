# External Libraries Utilization

## Overview
This document provides an overview of the external libraries used in this project, detailing their purposes and how they are utilized within the various components of our application.

## Libraries

### SQLite3
- **Purpose**: SQLite3 is used for local database management. It allows us to store and retrieve data related to the processing of MP3 files.
- **Usage in Project**: Utilized in the `DatabaseService` for creating the database, inserting records, and managing data related to MP3 file processing.

### TagLib
- **Purpose**: TagLib is employed for reading and editing the metadata of audio files, specifically MP3 tags.
- **Usage in Project**: Used in the `MP3TaggingService` to update the tags of MP3 files, including lyrics and other metadata.

### AWS SDK for C++
- **Purpose**: The AWS SDK for C++ is used to interact with AWS services, primarily for file upload functionality.
- **Usage in Project**: Integrated in the `UploadService` for uploading processed MP3 files to MinIO.

### librdkafka
- **Purpose**: librdkafka is a C++ client library for Apache Kafka, used for producing and consuming messages in a Kafka cluster.
- **Usage in Project**: Employed in the `NotificationService` to send notifications to Apache Kafka about the processing status of MP3 files.

### Boost.Process (part of Boost C++ Libraries)
- **Purpose**: Boost.Process is used for managing system processes, allowing the application to interface with external programs and scripts.
- **Usage in Project**: Utilized in the `TranscriptionService` to manage the invocation of the Python-based transcription script.

### spdlog
- **Purpose**: spdlog is a fast C++ logging library.
- **Usage in Project**: Used across various services for logging purposes, ensuring a consistent and efficient logging mechanism.

### yaml-cpp
- **Purpose**: yaml-cpp is a YAML parser and emitter for C++.
- **Usage in Project**: Used for parsing configuration files, allowing easy and flexible configuration of the application.

### Faster Whisper (Python Package)
- **Purpose**: Faster Whisper is a Python package used for audio transcription.
- **Usage in Project**: Called by the `TranscriptionService` to transcribe audio content from MP3 files.

## Adding New Libraries
When adding new external libraries to the project, please update this document accordingly, including the library's purpose and its usage within the project.

## Dependency Management
Ensure that all external libraries are properly documented in terms of version and configuration in the project's dependency management system to maintain consistency and ease of setup for new developers.
