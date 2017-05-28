#include "log.h"

#include <cstdarg>

namespace opengl_renderer {

std::string FormattedString(const char* fmt, ...) {
  char *buf = new char[DEFAULT_LOG_LENGTH];
  va_list args;
  va_start(args, fmt);
  std::vsnprintf(buf, DEFAULT_LOG_LENGTH, fmt, args);
  va_end(args);
  std::string buf_string(buf);
  delete[] buf;
  return buf_string;
}

void Log(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  printf(fmt, args);
  va_end(args);
}

void LogError(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  fprintf(stderr, fmt, args);
  va_end(args);
}

}  // opengl_renderer
