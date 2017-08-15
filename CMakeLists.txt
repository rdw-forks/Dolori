cmake_minimum_required(VERSION 2.6)

project(Dolori)

set(EXECUTABLE_OUTPUT_PATH bin)
file(
        GLOB_RECURSE
        source_files
        src/*
)

add_executable(
        dolori
        ${source_files}
)

if(WIN32)
  target_link_libraries(dolori wsock32 ws2_32)
endif()
