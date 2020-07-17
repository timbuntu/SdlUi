project(SdlUi)
cmake_minimum_required(VERSION 2.4)

if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
    cmake_policy(SET CMP0012 NEW)
    cmake_policy(SET CMP0054 NEW)
endif(COMMAND cmake_policy)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")
file(GLOB_RECURSE SOURCES
     ui/*.h
     ui/*.cpp
)

include(FindDoxygen)
if(DOXYGEN_FOUND)
    doxygen_add_docs(doc ui)
endif()

add_library(SdlUi SHARED ${SOURCES})
target_link_libraries(SdlUi SDL2 SDL2_image SDL2_ttf)
add_executable(debug tests/debug.cpp)
target_include_directories(debug PRIVATE ui)
target_link_libraries(debug SdlUi)

enable_testing()
set(CMAKE_CTEST_ARGUMENTS ${CMAKE_CTEST_ARGUMENTS} --output-on-failure)
file(GLOB testFiles "tests/test_*.cpp")
foreach(testFile ${testFiles})
    string(REGEX REPLACE "(^.*/|\\.[^.]*$)" "" output ${testFile})
    add_executable(${output} ${testFile})
    target_include_directories(${output} PRIVATE ui)
    target_link_libraries(${output} SdlUi)
    add_test(NAME ${output} COMMAND ${output})
endforeach()

