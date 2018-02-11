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

foreach(source IN LISTS DOLORI_FILES)
	get_filename_component(source_path "${source}" PATH)
	string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" rel_source_path "${source_path}")
	string(REPLACE "/" "\\" source_path_msvc "${rel_source_path}")
	source_group("${source_path_msvc}" FILES "${source}")
endforeach()

target_include_directories(${PROJECT_NAME} PRIVATE ".")

# Link libraries and add include directories for third parties
target_link_libraries(${PROJECT_NAME} tinyxml2)

target_include_directories(${PROJECT_NAME} PUBLIC ${IL_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${IL_LIBRARIES} ${ILUT_LIBRARIES})

target_include_directories(${PROJECT_NAME} PUBLIC ${ZLIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${ZLIB_LIBRARIES})

target_include_directories(${PROJECT_NAME} PUBLIC ${SDL2_TTF_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SDL2_TTF_LIBRARIES})

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})
target_include_directories(${PROJECT_NAME} PUBLIC ${OPENGL_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY})
target_include_directories(${PROJECT_NAME} PUBLIC ${SDL2_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} ${GLEW_LIBRARIES})
target_include_directories(${PROJECT_NAME} PUBLIC ${GLEW_INCLUDE_DIRS})

target_include_directories(${PROJECT_NAME} PUBLIC ${GLM_INCLUDE_DIRS})

if (WIN32)
	target_link_libraries(${PROJECT_NAME} wsock32 ws2_32)
endif ()