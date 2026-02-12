cmake_minimum_required(VERSION 3.10)
project(FlockingSim)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(libs/sfml)

add_executable(flocking_app main.cpp)

target_link_libraries(flocking_app sfml-graphics sfml-window sfml-system)