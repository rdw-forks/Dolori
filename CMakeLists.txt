cmake_minimum_required(VERSION 2.8.11)

project(Dolori)

set(EXECUTABLE_OUTPUT_PATH bin)

file(
        GLOB_RECURSE
        source_files
        src/*
)

add_executable(
        ${PROJECT_NAME}
        ${source_files}
)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/3rdparty/cmake" ${CMAKE_MODULE_PATH})

if(WIN32)
  # Tell CMake where to search for includes and libs on Windows
  set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH}
    "${PROJECT_SOURCE_DIR}/3rdparty/SDL2"
	"${PROJECT_SOURCE_DIR}/3rdparty/glew-2.1.0"
	"${PROJECT_SOURCE_DIR}/3rdparty/DevIL-1.8.0"
	"${PROJECT_SOURCE_DIR}/3rdparty/zlib-1.2.3"
  )
endif(WIN32)

find_package(OpenGL REQUIRED)
target_include_directories(${PROJECT_NAME} PUBLIC ${OPENGL_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})

find_package(SDL2 REQUIRED)
target_include_directories(${PROJECT_NAME} PUBLIC ${SDL2_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY})

find_package(GLEW REQUIRED)
target_include_directories(${PROJECT_NAME} PUBLIC ${GLEW_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${GLEW_LIBRARIES})

find_package(DevIL REQUIRED)
target_include_directories(${PROJECT_NAME} PUBLIC ${IL_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${IL_LIBRARIES} ${ILUT_LIBRARIES})

find_package(ZLIB REQUIRED)
target_include_directories(${PROJECT_NAME} PUBLIC ${ZLIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${ZLIB_LIBRARIES})


if(WIN32)
  target_link_libraries(${PROJECT_NAME} wsock32 ws2_32)
endif(WIN32)
