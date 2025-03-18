cmake_minimum_required(VERSION 3.19)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(RaytracingEngine)

file(GLOB SOURCES
    main.cpp
)
add_executable(${PROJECT_NAME} ${SOURCES})

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