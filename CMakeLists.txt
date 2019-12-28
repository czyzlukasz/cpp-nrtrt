cmake_minimum_required(VERSION 3.10)
project(cpp-nrtrt CXX)

set(CMAKE_CXX_STANDARD 17)

include_directories(Src)
include_directories(Src/glm)
include_directories(Src/Camera)
include_directories(Src/World)
include_directories(Src/Object)
include_directories(Src/RandGen)

add_library(Camera Src/Camera/Camera.cpp)
target_link_libraries(Camera sfml-graphics sfml-window sfml-system)

add_library(World Src/World/World.cpp)

add_library(RandGen Src/RandGen/RandGen.cpp)

add_executable(cpp-nrtrt Src/main.cpp)
target_link_libraries(cpp-nrtrt Camera World RandGen)

#UTs
enable_testing()
include_directories(Uts)
include(GoogleTest)
add_subdirectory(Uts/googletest)

add_executable(runUnitTests Uts/RayTest.cpp Uts/TriangleTest.cpp)
target_link_libraries(runUnitTests gtest gtest_main)