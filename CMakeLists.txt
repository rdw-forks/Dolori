cmake_minimum_required(VERSION 3.1)

project(Dolori CXX)

# Processing third parties
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/3rdparty/cmake" ${CMAKE_MODULE_PATH})
set_property(GLOBAL PROPERTY FIND_LIBRARY_USE_LIB64_PATHS ON)

# Tell CMake where to search for includes and libs on Windows
if (WIN32)
  set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH}
    "3rdparty/DevIL-1.8.0"
    "3rdparty/SDL2_ttf-2.0.14"
  )
endif ()

find_package(OpenGL REQUIRED)
find_package(DevIL REQUIRED)
find_package(SDL2_ttf REQUIRED)
set(GLM_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/3rdparty/glm/include")

add_compile_options("$<$<CONFIG:DEBUG>:-DDOLORI_DEBUG>")

add_subdirectory(3rdparty)
add_subdirectory(src)
