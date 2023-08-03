cmake_minimum_required(VERSION 3.11.0)
project(csgo-linux-cheat-base)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_C_COMPILER "/usr/bin/gcc")
set(CMAKE_CXX_COMPILER "/usr/bin/g++")

set(CMAKE_C_FLAGS_RELEASE "-W -Wall -Wextra -O3 -march=native -mtune=native -s -Wno-unused-variable -fvisibility=hidden -flto -fwhole-program -Wl,--strip-all")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} --no-gnu-unique -fno-rtti -std=c++2a")

set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--no-undefined")

file(GLOB_RECURSE SOURCE_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")
list(APPEND SOURCE_FILES "${CMAKE_SOURCE_DIR}/src/menu/ImGUI/GL/gl3w.c")

include_directories("${CMAKE_SOURCE_DIR}/src/")

add_library(csgo-linux-cheat-base SHARED ${SOURCE_FILES})
target_link_libraries(csgo-linux-cheat-base dl pthread SDL2 GL)