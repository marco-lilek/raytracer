cmake_minimum_required(VERSION 3.10)

set(THIRDPARTY src/thirdparty)
#set(CMAKE_EXPORT_COMPILE_COMMANDS 1) 
add_library(lodepng STATIC ${THIRDPARTY}/lodepng/lodepng.cpp ${THIRDPARTY}/lodepng/lodepng.h)

add_library(loguru ${THIRDPARTY}/loguru/loguru.cpp ${THIRDPARTY}/loguru/loguru.hpp)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(loguru Threads::Threads dl)

file(GLOB_RECURSE SOURCES src/*.cpp src/*.hpp src/*.h)

add_executable(raytracer ${SOURCES})

target_include_directories(raytracer SYSTEM PUBLIC ${THIRDPARTY})
target_include_directories(raytracer PUBLIC src)
target_compile_definitions(raytracer
    PUBLIC GLM_ENABLE_EXPERIMENTAL)

target_link_libraries(raytracer lodepng loguru)
