#include "image.h"

#include <cstdio>

namespace opengl_renderer {

Image Image::Create(const std::string& path) {
  Image image;
  image.Load(path);
  if (image.data_ == NULL) {
    return Image();
  }

  return image;
}

Image::~Image() {
  stbi_image_free(data_);
}

void Image::Load(const std::string& path) {
  path_ = path;
  data_ = stbi_load(path_.c_str(), &width_, &height_, &channel_count_, 0);
}

}  // opengl_renderer
