#include "image.h"

#include <cstdio>

namespace opengl_renderer {

Image Image::Create(const std::string& path) {
  Image image;
  image.Load(path);
  if (image.data_holder_.data_ == NULL) {
    fprintf(stderr, "Coundn't create image: %s\n", path.c_str());
    return Image();
  }

    fprintf(stderr, "Could create image: %s\n", path.c_str());
  return image;
}

Image::~Image() {
  printf("DESTRUCTOR: %p\n", data_holder_.data_);
  stbi_image_free(data_holder_.data_);
}

void Image::Load(const std::string& path) {
  data_holder_.path_ = path;
  printf("BEFORE: %p\n", data_holder_.data_);
  data_holder_.data_ = stbi_load(data_holder_.path_.c_str(),
                    &data_holder_.width_, &data_holder_.height_,
                    &data_holder_.channel_count_, 0);
  printf("AFTER: %p\n", data_holder_.data_);
}

}  // opengl_renderer
