file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/zlib
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/zlib ${CMAKE_CURRENT_BINARY_DIR}/zlib EXCLUDE_FROM_ALL)
target_include_directories(zlibstatic PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/zlib)
target_compile_definitions(zlibstatic PUBLIC Z_PREFIX)

if (WIN32)
target_compile_options(zlibstatic PRIVATE /MT$<$<CONFIG:Debug>:d>)
endif ()