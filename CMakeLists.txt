cmake_minimum_required(VERSION 3.0)

# C++ 11 Standards
set(CMAKE_CXX_STANDARD 11)

# Engine Project
project(Engine VERSION 1.0)
set(PROJECT_DIR ${CMAKE_SOURCE_DIR}/Engine)
include(${PROJECT_DIR}/CMakeLists.txt)

# Scripts
project(Scripts VERSION 1.0)
set(PROJECT_DIR ${CMAKE_SOURCE_DIR}/Scripts)
include(${PROJECT_DIR}/CMakeLists.txt)

# Game
project(CoinCollect VERSION 1.0)
set(PROJECT_DIR ${CMAKE_SOURCE_DIR}/CoinCollect)
include(${PROJECT_DIR}/CMakeLists.txt)
