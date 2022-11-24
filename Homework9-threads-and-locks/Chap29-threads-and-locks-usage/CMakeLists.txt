cmake_minimum_required(VERSION 3.23)
project(Chap29_threads_and_locks_usage)

set(CMAKE_CXX_STANDARD 17)

#add_executable(Chap29_threads_and_locks_usage main.cpp simpleCounter.cpp sloppyCounter.cpp concurrentLinkedList.cpp )
add_executable(Chap29_threads_and_locks_usage simpleQueue.cpp)
