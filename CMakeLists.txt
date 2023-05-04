cmake_minimum_required(VERSION 3.20)
project(Part2_Template)

set(CMAKE_CXX_STANDARD 14)

add_executable(Project2 FileChecker.cpp FileCopier.cpp main.cpp Project2MultiProcessModifier.cpp Util.cpp)
