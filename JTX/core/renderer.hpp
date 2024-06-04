#pragma once

#include "JTX/core/scene.hpp"
#include "JTX/core/shader.hpp"
#include "JTX/util/util.hpp"
#include "external/fpng.h"
#include <iostream>
#include <stdexcept>

namespace JTX::Core {
class Renderer {
public:
  Renderer(int w, int h, Shader *shader, int c = 3);
  ~Renderer() {
    delete[] fb_;
    delete[] zb_;
  };

  void clear();

  inline void drawPixel(int x, int y, int channel, float val) {
    if (x < 0 || x >= this->w_ || y < 0 || y >= this->h_ || channel < 0 ||
        channel >= this->c_) {
      throw std::invalid_argument("Pixel out of bounds or invalid channel");
    }
    this->fb_[(y * this->w_ * this->c_) + (x * this->c_) + channel] = val;
  }

  inline void drawPixel(int x, int y, float r, float g, float b) {
    if (x < 0 || x >= this->w_ || y < 0 || y >= this->h_ || this->c_ != 3) {
      throw std::invalid_argument("Pixel out of bounds or invalid channel");
    }
    int i = (y * this->w_ * this->c_) + (x * this->c_);
    this->fb_[i] = r;
    this->fb_[i + 1] = g;
    this->fb_[i + 2] = b;
  }

  inline float getPixel(int x, int y, int ch) {
    if (x < 0 || x >= this->w_ || y < 0 || y >= this->h_ || ch < 0 ||
        ch >= this->c_) {
      throw std::invalid_argument("Pixel out of bounds or invalid channel");
    }
    return this->fb_[(y * this->w_ * this->c_) + (x * this->c_) + ch];
  }

  // Bresenhams Line
  void drawLine(int x0, int y0, int x1, int y1, float r, float g, float b);
  inline void drawLine(int x0, int y0, int x1, int y1, JTX::Util::Color color) {
    drawLine(x0, y0, x1, y1, color.r, color.g, color.b);
  }

  // Bounding-box
  void drawTriangle(int x0, int y0, float z0, int x1, int y1, float z1, int x2,
                    int y2, float z2, float r, float g, float b);
  inline void drawTriangle(int x0, int y0, float z0, int x1, int y1, float z1,
                           int x2, int y2, float z2, JTX::Util::Color color) {
    drawTriangle(x0, y0, z0, x1, y1, z1, x2, y2, z2, color.r, color.g, color.b);
  }
  void rasterizeTriangle(const Scene &scene, const Primitive &prim,
                         const Face &face);

  void render(Scene *scene, ProjectionType projType = PERSPECTIVE);
  // THIS FUNCTION REQUIRES ALL VERTICES TO BE BETWEEN -1 AND 1
  void renderWireframe(JTX::Core::Primitive &p, JTX::Util::Color color);

  [[nodiscard]] int getWidth() const { return w_; }
  [[nodiscard]] int getHeight() const { return h_; }
  [[nodiscard]] int getChannels() const { return c_; }
  [[nodiscard]] float getAR() const { return ar_; }

  void saveFb(const std::string &path, int compressionLevel);

private:
  int w_, h_, c_;
  float ar_;
  float *fb_;
  float *zb_;
  Shader *shader_;

  static inline int edgeFn(int x0, int y0, int x1, int y1, int tx, int ty) {
    // This is the signed area of a parallelogram
    return (tx - x0) * (y1 - y0) - (ty - y0) * (x1 - x0);
  }

  inline float getDepth(int x, int y) {
    if (x < 0 || x >= this->w_ || y < 0 || y >= this->h_) {
      throw std::invalid_argument("Pixel out of bounds");
    }
    return this->zb_[y * this->w_ + x];
  }

  inline void setDepth(int x, int y, float z) {
    if (x < 0 || x >= this->w_ || y < 0 || y >= this->h_) {
      throw std::invalid_argument("Pixel out of bounds");
    }
    this->zb_[y * this->w_ + x] = z;
  }
};
} // namespace JTX::Core
