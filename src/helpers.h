#ifndef HELPERS_H
#define HELPERS_H

#include <string>

namespace opengl_renderer {
namespace helpers {

std::string LoadFile(const std::string& filepath);

std::string FormattedString(int buf_size, const char *fmt, ...);

}  // namespace helpers
}  // namespace opengl_renderer

#endif
