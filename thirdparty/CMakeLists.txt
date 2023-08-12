add_subdirectory(glad)

if(LOCAL_SDL)
    add_subdirectory(SDL EXCLUDE_FROM_ALL)
else()
    find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)
endif()

if(LOCAL_SPDLOG)
    add_subdirectory(spdlog)
else()
    find_package(spdlog REQUIRED)
endif()