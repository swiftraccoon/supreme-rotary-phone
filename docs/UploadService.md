# Upload Service

## Overview
The Upload Service is responsible for uploading processed MP3 files to MinIO, an object storage service. It handles file uploads and ensures that files are securely and efficiently transferred.

## Features
- Uploads MP3 files to a specified MinIO bucket.
- Configurable MinIO endpoint, access key, and secret key.

## Setup and Configuration
- Requires AWS SDK for C++.
- Configure MinIO connection details (endpoint, access key, secret key, and bucket) in the main configuration file.

## Usage
This service is invoked by the Audio Processing Orchestrator after the MP3 tagging process is complete.

## Dependencies
- AWS SDK for C++

## Troubleshooting
- Ensure MinIO server details are correctly configured.
- Verify network connectivity to the MinIO server.
- Check for errors related to AWS SDK or MinIO access permissions.
