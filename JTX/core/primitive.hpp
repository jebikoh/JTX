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

  [[nodiscard]] inline const Face *getFace(int i) const { return f_ + i; }
  inline Util::Vec3f getFaceNormal(int i) {
    float *n = n_ + 3 * i;
    return {n[0], n[1], n[2]};
  }

  inline Util::Vec4f getVertex(int i) {
    int j = 4 * i;
    return {v_[j], v_[j + 1], v_[j + 2], v_[j + 3]};
  }
  inline Util::Vec3f getVertexNormal(int i) {
    float *vn = vn_ + 3 * i;
    return {vn[0], vn[1], vn[2]};
  }
  inline Util::Vec3f getVertexTexture(int i) {
    float *vt = vt_ + 3 * i;
    return {vt[0], vt[1], vt[2]};
  }
  inline Util::Vec2i getScreen(int i) {
    int *s = getScreenPtr(i);
    return {s[0], s[1]};
  }
  inline float getZ(int i) { return z_[i]; }

  [[nodiscard]] inline int getNumVertices() const { return num_v_; };
  [[nodiscard]] inline int getNumFaces() const { return num_f_; };
  [[nodiscard]] inline int getNumVertexNormals() const { return num_vn_; };
  [[nodiscard]] inline int getNumVertexTextures() const { return num_vt_; };

private:
  int num_v_, num_vt_, num_vn_, num_f_;
  float *v_;
  float *vt_;
  float *vn_;
  float *z_;
  Face *f_;
  float *n_;
  int *screen_;

  inline int *getScreenPtr(int i) { return screen_ + 2 * i; }
  inline void setZ(int i, float z) { z_[i] = z; }

  friend class Renderer;
};
} // namespace JTX::Core
