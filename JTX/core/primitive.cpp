#include "primitive.hpp"

namespace JTX::Core {
const static int INITIAL_CAPACITY = 100;
const static int VERTEX_SIZE = 4;
const static int TEXTURE_SIZE = 3;
const static int NORMAL_SIZE = 3;
const static int FACE_SIZE = 1;

Primitive::Primitive()
    : num_v_(0), num_f_(0), num_vt_(0), num_vn_(0), v_(nullptr), vt_(nullptr),
      vn_(nullptr), f_(nullptr), n_(nullptr), screen_(nullptr) {}

Primitive::~Primitive() {
  delete[] v_;
  delete[] f_;
  delete[] n_;
}

/**
 * Resizes C-style array by allocating new array and copying contents. Deletes
 * old array. Does not check bounds (can cause segfaults if invalid capacity is
 * passed)
 * @tparam T Type of array
 * @param arr Array to resize (will be freed)
 * @param capacity Current array capacity. Will update to new capacity
 * @param new_capacity New array capacity
 * @param size Size per unit (e.g. 4 for a 4D vector). Defaults to 1
 * @param free_old Whether to free the old array. Defaults to true
 */
template <typename T>
void resize(T *&arr, int &capacity, int new_capacity, int size = 1,
            bool free_old = true) {
  capacity = new_capacity;
  auto *new_arr = new T[size * capacity];
  std::copy(arr, arr + size * capacity, new_arr);
  if (free_old)
    delete[] arr;
  arr = new_arr;
}

void Primitive::load(const std::string &path) {
  std::ifstream file(path);
  if (!file) {
    throw std::runtime_error("Error opening file: " + path);
  }

  int v_capacity = INITIAL_CAPACITY;
  int vt_capacity = INITIAL_CAPACITY;
  int vn_capacity = INITIAL_CAPACITY;
  int f_capacity = INITIAL_CAPACITY;
  v_ = new float[VERTEX_SIZE * v_capacity];
  vt_ = new float[TEXTURE_SIZE * vt_capacity];
  vn_ = new float[NORMAL_SIZE * vn_capacity];
  f_ = new Face[f_capacity];

  std::string line;
  while (std::getline(file, line)) {
    // VERTEX
    if (line.substr(0, 2) == "v ") {
      if (num_v_ == v_capacity) {
        resize(v_, v_capacity, 2 * v_capacity, VERTEX_SIZE);
      }
      std::istringstream iss(line.substr(2));
      float x, y, z;
      if (!(iss >> x >> y >> z)) {
        throw std::runtime_error("Error parsing vertex: " + line);
      }
      v_[VERTEX_SIZE * num_v_] = x;
      v_[VERTEX_SIZE * num_v_ + 1] = y;
      v_[VERTEX_SIZE * num_v_ + 2] = z;
      v_[VERTEX_SIZE * num_v_ + 3] = 1.0f;
      num_v_++;
    }
    // VERTEX TEXTURE
    else if (line.substr(0, 3) == "vt ") {
      if (num_vt_ == vt_capacity) {
        resize(vt_, vt_capacity, 2 * vt_capacity, TEXTURE_SIZE);
      }
      std::istringstream iss(line.substr(3));
      float u, v, w = 0.0f;
      if (!(iss >> u >> v)) {
        throw std::runtime_error("Error parsing texture vertex: " + line);
      }
      iss >> w;
      vt_[TEXTURE_SIZE * num_vt_] = u;
      vt_[TEXTURE_SIZE * num_vt_ + 1] = v;
      vt_[TEXTURE_SIZE * num_vt_ + 2] = w;
      num_vt_++;
    }
    // VERTEX NORMAL
    else if (line.substr(0, 3) == "vn ") {
      if (num_vn_ == vn_capacity) {
        resize(vn_, vn_capacity, 2 * vn_capacity, NORMAL_SIZE);
      }
      std::istringstream iss(line.substr(3));
      float x, y, z;
      if (!(iss >> x >> y >> z)) {
        throw std::runtime_error("Error parsing normal vertex: " + line);
      }
      vn_[NORMAL_SIZE * num_vn_] = x;
      vn_[NORMAL_SIZE * num_vn_ + 1] = y;
      vn_[NORMAL_SIZE * num_vn_ + 2] = z;
      num_vn_++;
    }
    // FACE
    else if (line.substr(0, 2) == "f ") {
      if (num_f_ == f_capacity) {
        resize(f_, f_capacity, 2 * f_capacity, FACE_SIZE);
      }
      std::istringstream iss(line.substr(2));
      std::string vert1, vert2, vert3;
      if (!(iss >> vert1 >> vert2 >> vert3)) {
        throw std::runtime_error("Error parsing face: " + line);
      }

      auto parse = [](const std::string &vert) {
        std::istringstream vert_iss(vert);
        std::string v_str, vt_str, vn_str;

        std::getline(vert_iss, v_str, '/');
        std::getline(vert_iss, vt_str, '/');
        std::getline(vert_iss, vn_str);

        int v = std::stoi(v_str) - 1;
        int vt = vt_str.empty() ? -1 : std::stoi(vt_str) - 1;
        int vn = vn_str.empty() ? -1 : std::stoi(vn_str) - 1;

        return std::make_tuple(v, vt, vn);
      };
      auto [v1, vt1, vn1] = parse(vert1);
      auto [v2, vt2, vn2] = parse(vert2);
      auto [v3, vt3, vn3] = parse(vert3);
      f_[num_f_] = {v1, v2, v3, vt1, vt2, vt3, vn1, vn2, vn3};
      num_f_++;
    }
  }

  v_ = reinterpret_cast<float *>(realloc(v_, 4 * num_v_ * sizeof(float)));
  f_ = reinterpret_cast<Face *>(realloc(f_, num_f_ * sizeof(Face)));
  n_ = new float[3 * num_f_];
  screen_ = new int[2 * num_v_];
}

void Primitive::calculateNormals() {
  for (int i = 0; i < this->num_f_; i++) {
    const auto &face = this->f_[i];
    const auto *v1 = this->getVertex(face.v1);
    const auto *v2 = this->getVertex(face.v2);
    const auto *v3 = this->getVertex(face.v3);

    JTX::Util::Vec3 e1(v2[0] - v1[0], v2[1] - v1[1], v2[2] - v1[2]);
    JTX::Util::Vec3 e2(v3[0] - v1[0], v3[1] - v1[1], v3[2] - v1[2]);

    JTX::Util::Vec3 normal = e1.cross(e2).normalize();

    this->n_[3 * i] = normal.x;
    this->n_[3 * i + 1] = normal.y;
    this->n_[3 * i + 2] = normal.z;
  }
}

void Primitive::applyTransform(const JTX::Util::Mat4 *tf) {
  auto *new_v = new float[4 * num_v_];
  cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasTrans, num_v_, 4, 4, 1.0f, v_,
              4, reinterpret_cast<const float *>(tf->data), 4, 0.0f, new_v, 4);
  delete[] v_;
  v_ = new_v;
}
} // namespace JTX::Core