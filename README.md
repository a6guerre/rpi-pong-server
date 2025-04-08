# RPI Pong Server

Raspberry Pi pong server for cloud-based pong game.
At a high-level, client will handle joystick events from player and then serialize the game input and send over to the server.

Server will update game state according to the user input, and send state to the clients participating in a multiplayer pong game.
---

## Prerequisites

Make sure you have the following installed:
cmake
g++

## Pulling RPI Pong Client and Flatbuffers submodule
```bash
git clone --recurse-submodule https://github.com/maxtek6/rpi-pong-server.git
cd rpi-pong-server
cd external/flatbuffers
git checkout v24.3.25
```
Note: Recurse flag is needed since the project requires building flatbuffers from source
Note: Due to versioning issues when installing flatbuffers from apt, checking out 24.3.25 branch and building that from source is what works for now.

## Building
1. Build flatbuffer from source (currently need to explictly build this version from source and run the built flatc compiler)
```bash
# Go to flatbuffers source directory, build flatc compiler from source and generate header file
cd <root-dir-proj>
cd external/flatbuffers
cmake -G "Unix Makefiles"
make -j
./flatc --cpp -o ../.. ../../pongdata.fbs

```
2. Building rpi-pong-server
```bash
# Build rpi server
cd <root-dir-proj>
mkdir build
cd build
cmake ..
make
```
3. Running server and client end to end
```bash
cd <rpi-server-dir>
cd build
./rpi-pong-server

# On a separate terminal with a joystick connected
cd <rpi-client-dir>
cd build
./rpi-pong-client

# To verify test functionality, move axes on joystick and verify that axes events are received by RPi Server
```

## Troubleshooting
```bash
cd <root-dir-proj>
./build/flatc --version 
# Ensure that version is 24.3.25 above
```
