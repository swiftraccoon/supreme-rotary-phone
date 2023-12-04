# MP3 Tagging Service

## Overview
The MP3 Tagging Service updates the tags of MP3 files, including lyrics and other metadata, based on the transcription results.

## Features
- Updates lyrics and other ID3 tags in MP3 files.
- Uses TagLib for tag manipulation.

## Setup and Configuration
- Requires TagLib library.
- No specific configuration needed for this service.

## Usage
This service is called by the Audio Processing Orchestrator after successful transcription of an MP3 file.

## Dependencies
- TagLib

## Troubleshooting
- Ensure TagLib is correctly installed and accessible.
- Verify that MP3 files are not write-protected.
