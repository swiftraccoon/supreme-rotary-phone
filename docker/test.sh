#!/bin/bash

# Run Docker Compose for Ubuntu
echo "Running build test in Ubuntu environment..."
sudo docker-compose -f build-testing/ubuntu/docker-compose.yml up --build

# Run Docker Compose for Fedora
echo "Running build test in Fedora environment..."
sudo docker-compose -f build-testing/fedora/docker-compose.yml up --build

# Clean up (optional)
echo "Cleaning up..."
sudo docker-compose -f build-testing/ubuntu/docker-compose.yml down
sudo docker-compose -f build-testing/fedora/docker-compose.yml down

echo "Build tests completed."