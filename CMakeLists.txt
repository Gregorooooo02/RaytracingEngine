cmake_minimum_required(VERSION 3.19)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(RaytracingEngine)

file(GLOB SOURCES
    main.cpp
    Math/*.cpp
    Utils/*.cpp
    Camera/*.cpp
)
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC Math Utils Camera)
