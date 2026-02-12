cmake_minimum_required(VERSION 3.10)
project(FlockingSim)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(libs/sfml)

file(GLOB SOURCE_FILES *.cpp)

add_executable(flocking_app ${SOURCE_FILES})

target_link_libraries(flocking_app sfml-graphics sfml-window sfml-system)