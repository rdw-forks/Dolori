enable_language(C)

set(GLAD_FILES
	"glad/src/glad.c"
)

add_library(glad STATIC ${GLAD_FILES})
target_include_directories(glad PUBLIC glad/include)