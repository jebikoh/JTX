#include "primitive.hpp"


namespace JTX::Core {

    const int INITIAL_CAPACITY = 100;

    Primitive::Primitive() : num_v_(0), num_f_(0), v_(nullptr), f_(nullptr), n_(nullptr), screen_(nullptr) {}

    Primitive::~Primitive() {
        delete[] v_;
        delete[] f_;
        delete[] n_;
    }

    void Primitive::load(const std::string &path) {
        std::ifstream file(path);
        if (!file) {
            throw std::runtime_error("Error opening file: " + path);
        }

        int v_capacity = INITIAL_CAPACITY;
        int f_capacity = INITIAL_CAPACITY;
        v_ = new float[4 * v_capacity];
        f_ = new Face[f_capacity];

        std::string line;
        while (std::getline(file, line)) {
            if (line.substr(0, 2) == "v ") {
                if (num_v_ == v_capacity) {
                    v_capacity *= 2;
                    auto* new_v = new float[4 * v_capacity];
                    std::copy(v_, v_ + 4 * num_v_, new_v);
                    delete[] v_;
                    v_ = new_v;
                }
                std::istringstream iss(line.substr(2));
                float x, y, z;
                if (!(iss >> x >> y >> z)) {
                    throw std::runtime_error("Error parsing vertex: " + line);
                }
                v_[4 * num_v_] = x;
                v_[4 * num_v_ + 1] = y;
                v_[4 * num_v_ + 2] = z;
                v_[4 * num_v_ + 3] = 1.0f;
                num_v_++;
            } else if (line.substr(0, 2) == "f ") {
                if (num_f_ == f_capacity) {
                    f_capacity *= 2;
                    auto* new_f = new Face[f_capacity];
                    std::copy(f_, f_ + num_f_, new_f);
                    delete[] f_;
                    f_ = new_f;
                }
                std::istringstream iss(line.substr(2));
                std::string vert1, vert2, vert3;
                if (!(iss >> vert1 >> vert2 >> vert3)) {
                    throw std::runtime_error("Error parsing face: " + line);
                }
                int v1 = std::stoi(vert1.substr(0, vert1.find('/'))) - 1;
                int v2 = std::stoi(vert2.substr(0, vert2.find('/'))) - 1;
                int v3 = std::stoi(vert3.substr(0, vert3.find('/'))) - 1;
                f_[num_f_] = {v1, v2, v3};
                num_f_++;
            }
        }

        v_ = reinterpret_cast<float*>(realloc(v_, 4 * num_v_ * sizeof(float)));
        f_ = reinterpret_cast<Face*>(realloc(f_, num_f_ * sizeof(Face)));
        n_ = new float[3 * num_f_];
        screen_ = new int[2 * num_v_];
    }

    void Primitive::calculateNormals() {
        for (int i = 0; i < this->num_f_; i++) {
            const auto& face = this->f_[i];
            const auto* v1 = this->getVertex(face.v1);
            const auto* v2 = this->getVertex(face.v2);
            const auto* v3 = this->getVertex(face.v3);

            JTX::Util::Vec3 e1(v2[0] - v1[0], v2[1] - v1[1], v2[2] - v1[2]);
            JTX::Util::Vec3 e2(v3[0] - v1[0], v3[1] - v1[1], v3[2] - v1[2]);

            JTX::Util::Vec3 normal = e1.cross(e2).normalize();

            this->n_[3 * i] = normal.x;
            this->n_[3 * i + 1] = normal.y;
            this->n_[3 * i + 2] = normal.z;
        }
    }

    void Primitive::applyTransform(const JTX::Util::Mat4* tf) {
        auto* new_v = new float[4 * num_v_];
        cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasTrans, num_v_, 4, 4, 1.0f,
                    v_, 4, reinterpret_cast<const float*>(tf->data), 4, 0.0f, new_v, 4);
        delete[] v_;
        v_ = new_v;
    }
} // JTX