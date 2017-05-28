#include "image.h"

#include <cstdio>

namespace opengl_renderer {

Image Image::Create(const std::string& path) {
  Image image;
  image.Load(path);
  if (image.data_holder_.data_ == NULL) {
    return Image();
  }
  return image;
}

void Image::Load(const std::string& path) {
  data_holder_.path_ = path;
  data_holder_.data_ = stbi_load(data_holder_.path_.c_str(),
      &data_holder_.width_, &data_holder_.height_,
      &data_holder_.channel_count_, 0);
}

}  // opengl_renderer
