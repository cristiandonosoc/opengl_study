#ifndef IMAGE_H
#define IMAGE_H

#include "stb_image.h"

#include <string>

namespace opengl_renderer {

class Image {
  public:
    static Image Create(const std::string& path);

  public:
    Image() = default;
    ~Image();

  public:
    Image(const Image& i) = delete;
    Image& operator=(const Image& i) = delete;

  public:
    Image(Image&& i) noexcept {
      data_holder_ = std::move(i.data_holder_);
      printf("[Image::move_ctor]\n");
    };

    Image& operator=(Image&& i) noexcept {
      data_holder_ = std::move(i.data_holder_);
      printf("[Image::move_assign]\n");
      return *this;
    };

  private:
    void Load(const std::string& path);


  public:
    int GetWidth() const { return data_holder_.width_; }
    int GetHeight() const { return data_holder_.height_; }
    int GetChannelCount() const { return data_holder_.channel_count_; }
    unsigned char *GetData() const { return data_holder_.data_; }

  private:
    struct Data {
      std::string path_;
      int width_ = 0;
      int height_ = 0;
      int channel_count_ = 0;
      unsigned char *data_ = nullptr;
    };
    Data data_holder_;
 };

}  // namespace opengl_renderer

#endif // IMAGE_H
