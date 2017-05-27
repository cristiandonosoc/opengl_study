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
    Image(Image&& i) = default;
    Image& operator=(Image&& i) = default;

  private:
    void Load(const std::string& path);


  public:
    int GetWidth() const { return width_; }
    int GetHeight() const { return height_; }
    int GetChannelCount() const { return channel_count_; }
    unsigned char *GetData() const { return data_; }

  private:
    std::string path_;
    int width_ = 0;
    int height_ = 0;
    int channel_count_ = 0;
    unsigned char *data_ = nullptr;
};

}  // namespace opengl_renderer

#endif // IMAGE_H
