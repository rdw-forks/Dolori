file(
	GLOB_RECURSE
	DOLORI_FILES
	*.cpp
	*.c
	*.h
)

add_executable(
	${PROJECT_NAME}
	${DOLORI_FILES}
)

set_target_properties(
	${PROJECT_NAME} PROPERTIES
	CXX_STANDARD 14
	CXX_STANDARD_REQUIRED ON
	COMPILE_FLAGS "${WARNING_FLAGS}"
)

# Add clang-tidy
if(DOLORI_USE_CLANG_TIDY AND CLANG_TIDY_EXE)
	set_target_properties(
		${PROJECT_NAME} PROPERTIES
		CXX_CLANG_TIDY "${DO_CLANG_TIDY}"
	)
endif()

foreach(source IN LISTS DOLORI_FILES)
	get_filename_component(source_path "${source}" PATH)
	string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" rel_source_path "${source_path}")
	string(REPLACE "/" "\\" source_path_msvc "${rel_source_path}")
	source_group("${source_path_msvc}" FILES "${source}")
endforeach()

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR})

# Link libraries and add include directories for third parties
target_link_libraries(${PROJECT_NAME} SDL2-static)
target_link_libraries(${PROJECT_NAME} glm)
target_link_libraries(${PROJECT_NAME} tinyxml2)
target_link_libraries(${PROJECT_NAME} grflib)
target_link_libraries(${PROJECT_NAME} glad)
target_link_libraries(${PROJECT_NAME} spdlog)
target_link_libraries(${PROJECT_NAME} zlibstatic)
target_link_libraries(${PROJECT_NAME} nlohmann_json)

target_include_directories(${PROJECT_NAME} PUBLIC ${IL_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${IL_LIBRARIES})

target_include_directories(${PROJECT_NAME} PUBLIC ${SDL2_TTF_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SDL2_TTF_LIBRARIES})

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})
target_include_directories(${PROJECT_NAME} PUBLIC ${OPENGL_INCLUDE_DIR})

if (WIN32)
	target_link_libraries(${PROJECT_NAME} wsock32 ws2_32)
endif ()

if (MSVC)
	target_compile_options(${PROJECT_NAME} PRIVATE /MT$<$<CONFIG:Debug>:d>)
	target_compile_options(${PROJECT_NAME} PRIVATE "/MP")
	target_compile_options(${PROJECT_NAME} PRIVATE "/EHsc")
	target_compile_options(${PROJECT_NAME} PRIVATE "/we4701")
endif ()
