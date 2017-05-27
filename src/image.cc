#include "image.h"

#include <cstdio>

namespace opengl_renderer {

Image Image::Create(const std::string& path) {
  Image image;
  image.Load(path);
  if (image.data_ == NULL) {
    fprintf(stderr, "Coundn't create image: %s\n", path.c_str());
    return Image();
  }

    fprintf(stderr, "Could create image: %s\n", path.c_str());
  return image;
}

Image::~Image() {
  printf("DESTRUCTOR: %p\n", data_);
  stbi_image_free(data_);
}

void Image::Load(const std::string& path) {
  path_ = path;
  printf("BEFORE: %p\n", data_);
  data_ = stbi_load(path_.c_str(), &width_, &height_, &channel_count_, 0);
  printf("AFTER: %p\n", data_);
}

}  // opengl_renderer
