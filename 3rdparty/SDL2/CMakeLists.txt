set(SDL_SHARED OFF CACHE BOOL "Build a shared version of the library")

if (WIN32)
  set(FORCE_STATIC_VCRT ON)
endif ()

add_subdirectory(SDL2 EXCLUDE_FROM_ALL)
target_include_directories(SDL2-static PUBLIC  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/SDL2/include>)
