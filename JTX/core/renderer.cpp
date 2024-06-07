#include "renderer.hpp"

JTX::Core::Renderer::Renderer(int w, int h, Shader *shader, int c) {
  if (w <= 0 || h <= 0 || c <= 0) {
    throw std::invalid_argument("Invalid dimensions");
  }

  this->w_ = w;
  this->h_ = h;
  this->c_ = c;
  this->ar_ = (float)w / (float)h;
  this->fb_ = new float[h * w * c]();
  this->zb_ = new float[h * w];
  this->shader_ = shader;

  for (int i = 0; i < w * h; i++) {
    this->zb_[i] = 0.0f;
  }
}

void JTX::Core::Renderer::clear() {
  // TODO: SIMD
  for (size_t i = 0; i < c_ * h_ * w_; i++) {
    fb_[i] = 0.0f;
  }
  for (size_t i = 0; i < h_ * w_; i++) {
    zb_[i] = 0.0f;
  }
}

void JTX::Core::Renderer::render(JTX::Core::Scene *scene,
                                 ProjectionType projType) {
  this->clear();
  JTX::Util::Mat4 t = scene->getCamera().getCameraMatrix(this->ar_, projType);
  // TODO: Rethink how the light is bound here
  UniformBuffer ub = {t, scene->getLight(0).getDirection()};
  this->shader_->bind(ub);

  auto wf = static_cast<float>(this->w_);
  auto hf = static_cast<float>(this->h_);
  for (auto const &[id, prim] : scene->getPrimitives()) {
    for (int i = 0; i < prim->getNumVertices(); i++) {
      // Clip space
      Util::Vec4f v = prim->getVertex(i);
      this->shader_->vertex(v);

      // NDC & Screen space transformation
      int *s = prim->getScreenPtr(i);
      s[0] = static_cast<int>(std::round((v.x / v.w + 1.0f) * 0.5f * wf));
      s[1] = static_cast<int>(std::round((v.y / v.w + 1.0f) * 0.5f * hf));
      prim->setZ(i, (v.z / v.w + 1.0f) * 0.5f);
    }

    for (int i = 0; i < prim->getNumFaces(); i++) {
      // Back-face culling
      Util::Vec3f n = prim->getFaceNormal(i);
      if (scene->getCamera().getLookAt().dot(n) >= -0.0001) {
        continue;
      }

      const Face *f = prim->getFace(i);
      Util::Vec2i v1 = prim->getScreen(f->v1);
      float z1 = prim->getZ(f->v1);

      Util::Vec2i v2 = prim->getScreen(f->v2);
      float z2 = prim->getZ(f->v2);

      Util::Vec2i v3 = prim->getScreen(f->v3);
      float z3 = prim->getZ(f->v3);

      // TODO: Move to rasterize function
      float intensity = 1.0f;
      if (scene->getNumLights() > 0) {
        intensity = 0.0f;
        for (int j = 0; j < scene->getNumLights(); ++j) {
          JTX::Core::DirLight light = scene->getLight(j);
          intensity += light.getIntensity(n);
        }
        intensity /= static_cast<float>(scene->getNumLights());
      }

      this->drawTriangle(v1, z1, v2, z2, v3, z3, 255.0f * intensity,
                         255.0f * intensity, 255.0f * intensity);
    }
  }
}

void JTX::Core::Renderer::renderWireframe(JTX::Core::Primitive &p,
                                          JTX::Util::Color color) {
  this->clear();
  auto w2 = 0.5f * static_cast<float>(this->w_);
  auto h2 = 0.5f * static_cast<float>(this->h_);

  JTX::Util::Mat4 scale = JTX::Util::Mat4::scale(w2 - 1.0f, h2 - 1.0f, 1);
  JTX::Util::Mat4 trans = JTX::Util::Mat4::translation(w2, h2, 0);

  p.applyTransform(&scale);
  p.applyTransform(&trans);

  for (int i = 0; i < p.getNumFaces(); i++) {
    const Core::Face *f = p.getFace(i);
    Util::Vec4f v1 = p.getVertex(f->v1);
    Util::Vec4f v2 = p.getVertex(f->v2);
    Util::Vec4f v3 = p.getVertex(f->v3);

    int v1_x = static_cast<int>(std::round(v1.x));
    int v1_y = static_cast<int>(std::round(v1.y));
    int v2_x = static_cast<int>(std::round(v2.x));
    int v2_y = static_cast<int>(std::round(v2.y));
    int v3_x = static_cast<int>(std::round(v3.x));
    int v3_y = static_cast<int>(std::round(v3.y));

    this->drawLine(v1_x, v1_y, v2_x, v2_y, color);
    this->drawLine(v2_x, v2_y, v3_x, v3_y, color);
    this->drawLine(v3_x, v3_y, v1_x, v1_y, color);
  }
}

void JTX::Core::Renderer::drawLine(int x0, int y0, int x1, int y1, float r,
                                   float g, float b) {
  if (x0 < 0 || x0 >= this->w_ || y0 < 0 || y0 >= this->h_ || x1 < 0 ||
      x1 >= this->w_ || y1 < 0 || y1 >= this->h_) {
    throw std::invalid_argument("Line out of bounds");
  }

  if (x0 == x1) {
    if (y0 > y1) {
      std::swap(y0, y1);
    }
    for (int y = y0; y <= y1; ++y) {
      drawPixel(x0, y, r, g, b);
    }
    return;
  }

  if (y0 == y1) {
    if (x0 > x1) {
      std::swap(x0, x1);
    }
    for (int x = x0; x <= x1; ++x) {
      drawPixel(x, y0, r, g, b);
    }
    return;
  }

  bool steep = std::abs(y1 - y0) > std::abs(x1 - x0);
  if (steep) {
    std::swap(x0, y0);
    std::swap(x1, y1);
  }
  if (x0 > x1) {
    std::swap(x0, x1);
    std::swap(y0, y1);
  }

  int dx = x1 - x0;
  int dy = std::abs(y1 - y0);
  int err = dx >> 1;
  int sy = (y0 < y1) ? 1 : -1;
  int y = y0;

  if (steep) {
    for (int x = x0; x <= x1; ++x) {
      drawPixel(y, x, r, g, b);
      err -= dy;
      if (err < 0) {
        y += sy;
        err += dx;
      }
    }
  } else {
    for (int x = x0; x <= x1; ++x) {
      drawPixel(x, y, r, g, b);
      err -= dy;
      if (err < 0) {
        y += sy;
        err += dx;
      }
    }
  }
}

void JTX::Core::Renderer::saveFb(const std::string &path,
                                 int compressionLevel) {
  if (this->c_ != 3) {
    throw std::invalid_argument("Invalid number of channels");
  }
  if (compressionLevel < 0 || compressionLevel > 9) {
    throw std::invalid_argument("Invalid compression level");
  }

  auto *pixels = new unsigned char[3 * this->w_ * this->h_];

  for (int y = 0; y < this->h_; ++y) {
    for (int x = 0; x < this->w_; ++x) {
      for (int ch = 0; ch < this->c_; ++ch) {
        float val = this->getPixel(x, y, ch);
        pixels[(y * this->w_ + x) * this->c_ + ch] =
            static_cast<unsigned char>(val);
      }
    }
  }
  bool success = fpng::fpng_encode_image_to_file(path.c_str(), pixels, this->w_,
                                                 this->h_, this->c_);

  if (success) {
    std::cout << "Image saved successfully: " << path << std::endl;
  } else {
    std::cerr << "Failed to save image: " << path << std::endl;
  }

  delete[] pixels;
}

void JTX::Core::Renderer::drawTriangle(Util::Vec2i v1, float z1, Util::Vec2i v2,
                                       float z2, Util::Vec2i v3, float z3,
                                       float r, float g, float b) {
  int minX = std::max(0, std::min(v1.x, std::min(v2.x, v3.x)));
  int minY = std::max(0, std::min(v1.y, std::min(v2.y, v3.y)));
  int maxX = std::min(this->w_ - 1, std::max(v1.x, std::max(v2.x, v3.x)));
  int maxY = std::min(this->h_ - 1, std::max(v1.y, std::max(v2.y, v3.y)));

  auto a = static_cast<float>(edgeFn(v1.x, v1.y, v2.x, v2.y, v3.x, v3.y));

  for (int y = minY; y <= maxY; ++y) {
    for (int x = minX; x <= maxX; ++x) {
      int w0 = edgeFn(v2.x, v2.y, v3.x, v3.y, x, y);
      int w1 = edgeFn(v3.x, v3.y, v1.x, v1.y, x, y);
      int w2 = edgeFn(v1.x, v1.y, v2.x, v2.y, x, y);

      if ((w0 >= 0 && w1 >= 0 && w2 >= 0) || (w0 <= 0 && w1 <= 0 && w2 <= 0)) {
        float wz0 = static_cast<float>(w0) / a;
        float wz1 = static_cast<float>(w1) / a;
        float wz2 = static_cast<float>(w2) / a;
        float z = wz0 * z1 + wz1 * z2 + wz2 * z3;

        if (z > this->getDepth(x, y)) {
          this->setDepth(x, y, z);
          this->drawPixel(x, y, r, g, b);
        }
      }
    }
  }
}

// void JTX::Core::Renderer::rasterizeTriangle(const JTX::Core::Scene &scene,
//                                             const JTX::Core::Primitive &prim,
//                                             const JTX::Core::Face &face) {
//   if (!this->shader_->isBound()) {
//     throw std::runtime_error("Shader not bound");
//   }
//
//   // Screen XY
//   const int *v1 = prim.getScreen(face.v1);
//   const int x1 = v1[0];
//   const int y1 = v1[1];
//
//   const int *v2 = prim.getScreen(face.v2);
//   const int x2 = v2[0];
//   const int y2 = v2[1];
//
//   const int *v3 = prim.getScreen(face.v3);
//   const int x3 = v3[0];
//   const int y3 = v3[1];
//
//   // Z
//   const float z1 = prim.getVertex(face.v1)[2];
//   const float z2 = prim.getVertex(face.v2)[2];
//   const float z3 = prim.getVertex(face.v3)[2];
//
//   int minX = std::max(0, std::min(x1, std::min(x2, x3)));
//   int minY = std::max(0, std::min(y1, std::min(y2, y3)));
//   int maxX = std::min(this->w_ - 1, std::max(x1, std::max(x2, x3)));
//   int maxY = std::min(this->h_ - 1, std::max(y1, std::max(y2, y3)));
//
//   auto a = static_cast<float>(edgeFn(x1, y1, x2, y2, x3, y3));
//
//   for (int y = minY; y <= maxY; ++y) {
//     for (int x = minX; x <= maxX; ++x) {
//       int w0 = edgeFn(x2, y2, x3, y3, x, y);
//       int w1 = edgeFn(x3, y3, x1, y1, x, y);
//       int w2 = edgeFn(x1, y1, x2, y2, x, y);
//
//       if ((w0 >= 0 && w1 >= 0 && w2 >= 0) || (w0 <= 0 && w1 <= 0 && w2 <= 0))
//       {
//         float wz0 = static_cast<float>(w0) / a;
//         float wz1 = static_cast<float>(w1) / a;
//         float wz2 = static_cast<float>(w2) / a;
//         float z = wz0 * z1 + wz1 * z2 + wz2 * z3;
//
//         if (z > this->getDepth(x, y)) {
//           this->setDepth(x, y, z);
//           this->drawPixel(x, y, 0.0f, 0.0f, 0.0f);
//         }
//       }
//     }
//   }
// }
