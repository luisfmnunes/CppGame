add_executable(${PROJECT_NAME})

file(GLOB CORE_SOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/core/*.cpp)
file(GLOB MANAGER_SOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/manager/*.cpp )

target_sources(${PROJECT_NAME} PRIVATE main.cpp engine.cpp ${CORE_SOURCES} ${MANAGER_SOURCES})
target_include_directories( 
    ${PROJECT_NAME} 
    PRIVATE ${CMAKE_SOURCE_DIR}/include 
    INTERFACE ${CMAKE_SOURCE_DIR}/thirdparty/spdlog/include
    INTERFACE ${CMAKE_SOURCE_DIR}/thirdparty/glad/include
)
target_link_libraries(${PROJECT_NAME} glad SDL3::SDL3 spdlog::spdlog)

target_compile_definitions(${PROJECT_NAME} PRIVATE GAME_MAJOR_VERSION=${CMAKE_PROJECT_VERSION_MAJOR})
target_compile_definitions(${PROJECT_NAME} PRIVATE GAME_MINOR_VERSION=${CMAKE_PROJECT_VERSION_MINOR})

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PRIVATE GAME_DEBUG=1)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(${PROJECT_NAME} PRIVATE GAME_RELEASE=1)
endif()