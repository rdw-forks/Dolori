add_library(tinyxml2 STATIC tinyxml2/tinyxml2.cpp tinyxml2/tinyxml2.h)
target_include_directories(tinyxml2 PUBLIC tinyxml2)

if (WIN32)
  target_compile_options(tinyxml2 PRIVATE /MT$<$<CONFIG:Debug>:d>)
endif ()