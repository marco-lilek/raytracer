cmake_minimum_required(VERSION 3.15)
set(CMAKE_FIND_DEBUG_MODE 1)
project(raytracer2)

set(CMAKE_CXX_STANDARD 14)
set(THIRDPARTY_ROOT thirdparty)
set(THREADS_PREFER_PTHREAD_FLAG ON)

include_directories(BEFORE SYSTEM include)
link_directories(lib)

add_library(polyroots ${THIRDPARTY_ROOT}/polyroots.cpp)
add_library(lodepng ${THIRDPARTY_ROOT}/lodepng.cpp)
find_package(fmt REQUIRED)
find_package(Threads REQUIRED)
find_package(Lua "5.3" REQUIRED)
find_package(Assimp "4.1" REQUIRED)
find_package(spdlog REQUIRED)
file(GLOB SOURCES src/*.cpp src/*.hpp src/*.h)
add_executable(raytracer ${SOURCES})

get_directory_property( DirDefs COMPILE_DEFINITIONS )

target_compile_definitions(raytracer PUBLIC GLM_ENABLE_EXPERIMENTAL)

target_link_libraries(
        raytracer
        polyroots
        lodepng
        fmt
        spdlog::spdlog
        ${LUA_LIBRARIES}
        ${ASSIMP_LIBRARIES})
set(CMAKE_EXPORT_COMPILE_COMMANDS YES)
file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/logs")
