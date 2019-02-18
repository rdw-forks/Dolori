#ifndef DOLORI_COMMON_DEBUG_H_
#define DOLORI_COMMON_DEBUG_H_

#include <spdlog/spdlog.h>

#ifdef DOLORI_DEBUG
#define DOLORI_LOGGER_NAME "Dolori"
#define LOG(LEVEL, FMT, ...) \
  spdlog::get(DOLORI_LOGGER_NAME)->LEVEL(FMT, ##__VA_ARGS__)
#else
#define LOG(CHANNEL, FMT, ...)
#endif  // DOLORI_DEBUG

#endif  // DOLORI_COMMON_DEBUG_H_
