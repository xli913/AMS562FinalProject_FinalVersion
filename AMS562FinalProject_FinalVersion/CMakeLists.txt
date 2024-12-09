cmake_minimum_required(VERSION 3.15)

# Project Name
project(DeliveryScheduler LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add subdirectories for source and tests
add_subdirectory(src)
add_subdirectory(tests)

