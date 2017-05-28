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
    ~Image() = default;

  public:
    Image(const Image& i) = delete;
    Image& operator=(const Image& i) = delete;

  public:
    Image(Image&& i) noexcept {
      Move(std::move(i));
    };

    Image& operator=(Image&& i) noexcept {
      if (this != &i) {
        Destroy();
      }
      Move(std::move(i));
      return *this;
    };

  private:
    void Load(const std::string& path);

  private:
    void Move(Image&& i) {
      data_holder_ = std::move(i.data_holder_);
      // We clear the data
      i.data_holder_ = Image::Data();
    }

    void Destroy() {
      if (data_holder_.data_ != nullptr) {
        stbi_image_free(data_holder_.data_);
      }
      data_holder_ = Image::Data();
    }


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
