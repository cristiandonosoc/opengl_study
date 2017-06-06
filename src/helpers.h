#ifndef HELPERS_H
#define HELPERS_H

#include <string>

namespace opengl_renderer {
namespace helpers {

std::string LoadFile(const std::string& filepath);

std::string FormattedString(const char *fmt, ...);
std::string FormattedString(int buf_size, const char *fmt, ...);

void Log(const char* fmt, ...);
void LogError(const char *fmt, ...);

}  // namespace helpers
}  // namespace opengl_renderer

#endif
