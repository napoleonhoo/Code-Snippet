#ifndef NPJH_MAPREDUCE_COMMON_LOG_H_
#define NPJH_MAPREDUCE_COMMON_LOG_H_

#include <stdio.h>

namespace npjh {

#define LOG(format, ...) printf(format, ##__VA_ARGS__)

#define LOG_DEBUG(format, ...)                                       \
  printf("[DEBUG][%s][%s][%d]" format, __FILE__, __func__, __LINE__, \
         ##__VA_ARGS__)
#define LOG_INFO(format, ...)                                       \
  printf("[INFO][%s][%s][%d]" format, __FILE__, __func__, __LINE__, \
         ##__VA_ARGS__)
#define LOG_WARN(format, ...)                                       \
  printf("[WARN][%s][%s][%d]" format, __FILE__, __func__, __LINE__, \
         ##__VA_ARGS__)
#define LOG_ERROR(format, ...)                                       \
  printf("[ERROR][%s][%s][%d]" format, __FILE__, __func__, __LINE__, \
         ##__VA_ARGS__)
#define LOG_FATAL(format, ...)                                       \
  printf("[FATAL][%s][%s][%d]" format, __FILE__, __func__, __LINE__, \
         ##__VA_ARGS__)

}  // namespace npjh

#endif