cmake_minimum_required(VERSION 3.10)

# Project name
project(rpi-pong-server)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Install directory of flatbuffers
set(CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/../flatbuffers/install")

# Find FlatBuffers (this uses the FlatBuffersConfig.cmake from the install)
find_package(Flatbuffers REQUIRED CONFIG)

# Add the executable
add_executable(rpi-pong-server src/RpiPongServer.cpp src/main.cpp)

target_include_directories(rpi-pong-server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include 
                                                   ${CMAKE_SOURCE_DIR}/../flatbuffers/install/include
                                                   ${CMAKE_CURRENT_SOURCE_DIR}/../generated)
# Link to flatbuffers
target_link_libraries(rpi-pong-server PRIVATE flatbuffers::flatbuffers)
