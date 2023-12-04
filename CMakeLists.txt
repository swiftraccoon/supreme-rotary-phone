cmake_minimum_required(VERSION 3.16)

project(AudioProcessingProject)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Creates a variable with all your .cpp files
file(GLOB source_files
    "src/*.cpp"
)

# Add all include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    /usr/local/include # Replace with your systems' include path for third-party libraries if needed
    # Other include paths for spdlog, yaml-cpp or other libraries if they're not in the system path
)

# Add path where CMake can find your Find<Package>.cmake modules (if not using standard packages)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# BOOST - Used for process management interop with Python and more
find_package(Boost 1.71 REQUIRED COMPONENTS system filesystem)

# TagLib - Used for mp3 tagging
find_package(TagLib REQUIRED)

# yaml-cpp - Used for configuration files
find_package(yaml-cpp REQUIRED)

# SQLite3 - Used for local database interactions
find_package(SQLite3 REQUIRED)

# AWS SDK - Needed for interaction with MinIO
find_package(AWSSDK REQUIRED COMPONENTS s3)

# RdKafka - C++ client for Apache Kafka
find_package(RdKafka REQUIRED)

# Add the executable that is being built from the source files
add_executable(${PROJECT_NAME} ${source_files})

# Link all the necessary libraries
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    ${Boost_LIBRARIES}
    ${TAGLIB_LIBRARIES}
    ${YAML_CPP_LIBRARIES}
    ${SQLite3_LIBRARIES}
    ${AWSSDK_LINK_LIBRARIES}
    ${RDKAFKA_LIBRARIES}
    pthread # Required for threading
    # You might need to link other system libraries depending on your environment
)