# Audio Processing Orchestrator

## Overview
The Audio Processing Orchestrator is the central component of the project, coordinating the workflow among various services like file monitoring, transcription, tagging, uploading, and notification.

## Features
- Orchestrates the workflow of processing MP3 files.
- Manages interactions between different services.
- Handles error scenarios and logs processing details.

## Setup and Configuration
- Requires configuration details for all integrated services.
- Set up the main configuration file with paths, service parameters, and logging details.

## Usage
Run the orchestrator with the configuration file path as an argument. It automatically manages the processing of MP3 files from monitoring to uploading and notification.

## Dependencies
- Dependent on all other services (FileMonitorService, TranscriptionService, MP3TaggingService, UploadService, DatabaseService, NotificationService).

## Troubleshooting
- Ensure all service dependencies are correctly set up and configured.
- Check the orchestrator's logs for errors in service interactions or workflow execution.
