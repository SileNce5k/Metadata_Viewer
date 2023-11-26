#!/bin/bash
set -xe
# Build
g++ -o parse main.cpp

# Run
./parse test_file.mp3
