cmake_minimum_required(VERSION 3.0.0)
project(cppgame)
set(CMAKE_CXX_STANDARD 23)

option (LOCAL_SDL "Use locally built SDL" OFF)
option (LOCAL_SPDLOG "Use locally built SPDLOG" OFF)

add_subdirectory(thirdparty)
add_subdirectory(src)
