project(SdlUi)
cmake_minimum_required(VERSION 2.4)

if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")
file(GLOB_RECURSE SOURCES
     ui/*.h
     ui/*.cpp
)

add_library(SdlUi SHARED ${SOURCES})
target_link_libraries(SdlUi SDL2 SDL2_image SDL2_ttf)
add_executable(test tests/main.cpp)
target_include_directories(test PRIVATE ui)
target_link_libraries(test SdlUi)
