cmake_minimum_required(VERSION 3.0.0)
project(cppgame VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 23)

option (LOCAL_SDL "Use locally built SDL" OFF)
option (LOCAL_SPDLOG "Use locally built SPDLOG" OFF)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/debug)
endif()

add_subdirectory(thirdparty)
add_subdirectory(src)
