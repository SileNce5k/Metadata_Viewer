#!/bin/bash
set -xe
# Build
g++ -o parse main.cpp -pedantic -Wall -Wno-unused-variable
