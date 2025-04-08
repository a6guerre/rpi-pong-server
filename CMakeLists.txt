cmake_minimum_required(VERSION 3.10)

# Project name
project(rpi-pong-server)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add flatbuffers subdir
add_subdirectory(external/flatbuffers)

# Add the executable
add_executable(rpi-pong-server RpiPongServer.cpp main.cpp)

target_include_directories(rpi-pong-server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Link against flatbuffers
target_link_libraries(rpi-pong-server PRIVATE flatbuffers)
