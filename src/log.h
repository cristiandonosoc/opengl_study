#ifndef LOG_H
#define LOG_H

#include <string>
#include <cstdio>

#define DEFAULT_LOG_LENGTH 100

namespace opengl_renderer {


// This methods use DEFAULT_LOG_LENGTH
std::string FormattedString(const char *fmt, ...);
void Log(const char* fmt, ...);
void LogError(const char *fmt, ...);

}  // namespace opengl_renderer

#endif
