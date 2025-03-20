cmake_minimum_required(VERSION 3.19)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Use a custom CMakeList to find GLFW
if(WIN32)
    list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
endif()

project(RaytracingEngine)

file(GLOB SOURCES
    main.cpp
    Window/*.cpp
    Math/*.cpp
)
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC Window)

find_package(glfw3 3.3 REQUIRED)
find_package(Vulkan REQUIRED)

if(UNIX)
    set(GLFW3_LIBRARY glfw)
endif()

if(MSVC)
    target_link_libraries(${PROJECT_NAME} ${GLFW3_LIBRARY} Vulkan::Vulkan)
else()
    target_link_libraries(${PROJECT_NAME} ${GLFW3_LIBRARY} Vulkan::Vulkan stdc++ m)
endif()
