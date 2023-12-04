# File Monitor Service

## Overview
The File Monitor Service is responsible for monitoring a specified directory for new MP3 files. When a new file is detected, it triggers the transcription and tagging process.

## Features
- Monitors a specified directory for new MP3 files.
- Uses `inotify` for efficient file system monitoring.
- Integrates with the orchestrator to trigger further processing of detected files.

## Setup and Configuration
- Ensure `inotify` is supported on your system.
- Configure the monitored directory path in the main configuration file.

## Usage
The service is automatically started by the Audio Processing Orchestrator and requires no manual intervention.

## Dependencies
- `inotify` (Linux-specific)

## Troubleshooting
- Ensure the service has read permissions for the monitored directory.
- Check system logs for any `inotify` related errors.
