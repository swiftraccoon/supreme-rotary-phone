# Database Service

## Overview
The Database Service manages interactions with the project's SQLite database. It handles operations such as initializing the database and inserting records for processed MP3 files.

## Features
- Initializes the SQLite database with the required schema.
- Inserts and manages records related to MP3 file processing.

## Setup and Configuration
- Requires SQLite3.
- Specify the database file path in the main configuration file.

## Usage
The service is utilized by the Audio Processing Orchestrator to log details about each processed MP3 file, including transcription and tagging information.

## Dependencies
- SQLite3

## Troubleshooting
- Ensure the database file path is correctly configured and accessible.
- Check for errors related to database permissions or schema issues.
