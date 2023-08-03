add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE main.cpp)
target_include_directories( ${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include )
target_link_libraries(${PROJECT_NAME} INTERFACE SDL3::SDL3 INTERFACE spdlog)