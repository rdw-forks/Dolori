set(GRFLIB_FILES
	"grflib/grfcrypt.cpp"
	"grflib/grftypes.h"
	"grflib/grfcrypt.h"
)

add_library(grflib STATIC ${GRFLIB_FILES})
target_include_directories(grflib PUBLIC grflib)