#include "helpers.h"
#include "log.h"

#include <memory>
#include <cstdio>
#include <cstdarg>

namespace opengl_renderer {
namespace helpers {

namespace {

// Deleter to be used with unique_ptr for malloc-ed pointers
template<typename T>
struct Deleter {
  void operator()(T *ptr) {
    if (ptr) { free(ptr); }
  }
};

// File specialization
template<>
struct Deleter<FILE> {
  void operator()(FILE *file) {
    if (file) { fclose(file); }
  }
};

}  // namespace

std::string LoadFile(const std::string& filepath) {
  FILE *file = fopen(filepath.c_str(), "r");
  // We wrap in unique_ptr so we don't have to worry about lifetime
  std::unique_ptr<FILE, Deleter<FILE>> file_unique_ptr(file);

  if (!file) {
    LogError("Could open file %s", filepath.c_str());
    return "";
  }

  // We seek to the end to find the length
  fseek(file, 0, SEEK_END);
  size_t file_length = ftell(file);
  rewind(file);

  std::unique_ptr<char, Deleter<char>> buffer;
  buffer.reset((char*)malloc((file_length + 1) * sizeof(char)));

  size_t read_result = fread(buffer.get(), file_length, 1, file);
  if (read_result != 1) {
    LogError("Didn't read whole file: %lu vs  %lu\n", read_result, file_length);
  }
  std::string result(buffer.get());
  return result;
}

std::string FormattedString(int buf_size, const char* fmt, ...) {
  char *buf = new char[buf_size];
  va_list args;
  va_start(args, fmt);
  vsnprintf(buf, buf_size, fmt, args);
  va_end(args);
  std::string buf_string(buf);
  delete[] buf;
  return buf_string;
}

}  // namespace helpers
}  // namespace opengl_renderer
