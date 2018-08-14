#include "Common/debug.h"

#include <spdlog/sinks/stdout_color_sinks.h>

#ifdef DOLORI_DEBUG
static auto g_logger = spdlog::stdout_color_mt(DOLORI_LOGGER_NAME);
#endif  // DOLORI_DEBUG
