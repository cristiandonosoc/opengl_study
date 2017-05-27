#ifndef IMAGE_H
#define IMAGE_H

#include "stb_image.h"

#include <string>

namespace opengl_renderer {

class Image {
  public:
    static Image Create(const std::string& path);

  private:
    void Load(const std::string& path);

  private:
    ~Image();

  private:
    void Free();

  private:
    std::string path_;
    int width_ = 0;
    int height_ = 0;
    int channel_count_ = 0;
    unsigned char *data_;
};

}  // namespace opengl_renderer

#endif // IMAGE_H
