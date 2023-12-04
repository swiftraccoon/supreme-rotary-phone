# Supreme Rotary Phone - Audio Processing Suite

## Overview
Supreme Rotary Phone is a comprehensive audio processing suite designed to handle various aspects of MP3 file management, including monitoring, transcription, tagging, uploading, and notification. This project aims to provide a robust and efficient solution for processing audio files, with a focus on strict type checking, optimization, and professional-grade documentation and readability.

## Features
- **File Monitoring**: Monitors a specified directory for new MP3 files.
- **Transcription Service**: Transcribes audio content from MP3 files using the Faster Whisper model.
- **MP3 Tagging**: Updates MP3 tags, including lyrics and other metadata.
- **Database Service**: Manages data storage related to MP3 file processing.
- **Upload Service**: Handles the uploading of processed files to MinIO.
- **Notification Service**: Sends notifications to Apache Kafka regarding the processing status of MP3 files.

## Getting Started

### Prerequisites
- C++20 compatible compiler
- Python 3.x
- SQLite3
- TagLib
- AWS SDK for C++
- librdkafka
- Boost C++ Libraries
- spdlog
- yaml-cpp
- Faster Whisper (Python package)

### Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/swiftraccoon/supreme-rotary-phone.git
   ```
2. Navigate to the project directory:
   ```bash
   cd supreme-rotary-phone
   ```
3. Install necessary packages
- RedHat based:
   ```bash
   sudo dnf install spdlog-devel yaml-cpp-devel sqlite-devel boost-devel taglib-devel librdkafka-devel
   ```
- Debian based:
   ```bash
   sudo apt-get install libspdlog-dev libyaml-cpp-dev libsqlite3-dev libboost-all-dev libtag1-dev librdkafka-dev
   ```

### Configuration
- Modify the `config.yaml.example` file to set up the necessary configurations for each service.
- Rename `config.yaml.example` to `config.yaml`.

## Usage
TBD

## Services
Each service in this suite is designed to perform specific tasks in the audio processing workflow. 

Detailed information about each service can be found in their respective `README.md` files in the `docs/` directory.

## Contributing
Contributions to the Supreme Rotary Phone project are welcome. 

Please read `CONTRIBUTING.md` for details on our code of conduct and the process for submitting pull requests.

## Versioning
TBD

## Authors
- **swiftraccoon** - *Initial work* - [swiftraccoon](https://github.com/swiftraccoon)

## License
This project is licensed under the GPL3 License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments
TBD
