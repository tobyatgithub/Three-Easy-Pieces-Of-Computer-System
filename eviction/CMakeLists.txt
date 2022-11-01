cmake_minimum_required(VERSION 3.23)
project(eviction)

set(CMAKE_CXX_STANDARD 17)

add_executable(eviction main.cpp SwapManager.cpp SwapManager.h)
