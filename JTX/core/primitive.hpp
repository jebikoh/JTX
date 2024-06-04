#pragma once

#include "JTX/util/util.hpp"
#include <cblas.h>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>

namespace JTX::Core {

struct Face {
  int v1, v2, v3;
  int vt1, vt2, vt3;
  int vn1, vn2, vn3;
};

class Primitive {
public:
  Primitive();
  ~Primitive();

  void load(const std::string &path);
  void applyTransform(const JTX::Util::Mat4 *tf);
  void calculateNormals();

  inline float *getNormal(int i) { return n_ + 3 * i; }
  [[nodiscard]] inline const float *getFaceNormal(int i) const {
    return n_ + (3 * i);
  };

  inline float *getVertex(int i) { return v_ + 4 * i; }
  inline float *getVertexNormal(int i) { return vn_ + 3 * i; }
  inline float *getVertexTexture(int i) { return vt_ + 3 * i; }

  [[nodiscard]] inline const float *getVertex(int i) const {
    return v_ + 4 * i;
  }
  [[nodiscard]] inline const float *getVertexNormal(int i) const {
    return vn_ + 3 * i;
  }
  [[nodiscard]] inline const float *getVertexTexture(int i) const {
    return vt_ + 3 * i;
  }

  inline int *getScreen(int i) { return screen_ + 2 * i; }
  [[nodiscard]] inline const int *getScreen(int i) const {
    return screen_ + 2 * i;
  }

  [[nodiscard]] inline Face *getFace(int i) { return f_ + i; }
  [[nodiscard]] inline const Face *getFace(int i) const { return f_ + i; }

  [[nodiscard]] inline int getNumVertices() const { return num_v_; };
  [[nodiscard]] inline int getNumFaces() const { return num_f_; };
  [[nodiscard]] inline int getNumVertexNormals() const { return num_vn_; };
  [[nodiscard]] inline int getNumVertexTextures() const { return num_vt_; };

private:
  int num_v_, num_vt_, num_vn_, num_f_;
  float *v_;
  float *vt_;
  float *vn_;
  Face *f_;
  float *n_;
  int *screen_;
};
} // namespace JTX::Core
