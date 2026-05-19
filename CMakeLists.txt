cmake_minimum_required(VERSION 3.10)
project(AtariAdventureClone VERSION 1.0)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

set(SOURCES src/main.cpp src/juego.cpp)

add_executable(AtariGame ${SOURCES})