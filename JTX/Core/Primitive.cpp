#include "Primitive.h"


namespace JTX::Core {

    const int INITIAL_CAPACITY = 100;

    Primitive::Primitive() : num_v(0), num_f(0), v(nullptr), f(nullptr), n(nullptr) {}

    Primitive::~Primitive() {
        delete[] v;
        delete[] f;
        delete[] n;
    }

    void Primitive::load(const std::string &path) {
        std::ifstream file(path);
        if (!file) {
            throw std::runtime_error("Error opening file: " + path);
        }

        int v_capacity = INITIAL_CAPACITY;
        int f_capacity = INITIAL_CAPACITY;
        v = new float[4 * v_capacity];
        f = new Face[f_capacity];

        std::string line;
        while (std::getline(file, line)) {
            if (line.substr(0, 2) == "v ") {
                if (num_v == v_capacity) {
                    v_capacity *= 2;
                    auto* new_v = new float[4 * v_capacity];
                    std::copy(v, v + 4 * num_v, new_v);
                    delete[] v;
                    v = new_v;
                }
                std::istringstream iss(line.substr(2));
                float x, y, z;
                if (!(iss >> x >> y >> z)) {
                    throw std::runtime_error("Error parsing vertex: " + line);
                }
                v[4 * num_v] = x;
                v[4 * num_v + 1] = y;
                v[4 * num_v + 2] = z;
                v[4 * num_v + 3] = 1.0f;
                num_v++;
            } else if (line.substr(0, 2) == "f ") {
                if (num_f == f_capacity) {
                    f_capacity *= 2;
                    auto* new_f = new Face[f_capacity];
                    std::copy(f, f + num_f, new_f);
                    delete[] f;
                    f = new_f;
                }
                std::istringstream iss(line.substr(2));
                std::string vert1, vert2, vert3;
                if (!(iss >> vert1 >> vert2 >> vert3)) {
                    throw std::runtime_error("Error parsing face: " + line);
                }
                int v1 = std::stoi(vert1.substr(0, vert1.find('/'))) - 1;
                int v2 = std::stoi(vert2.substr(0, vert2.find('/'))) - 1;
                int v3 = std::stoi(vert3.substr(0, vert3.find('/'))) - 1;
                f[num_f] = {v1, v2, v3};
                num_f++;
            }
        }

        v = reinterpret_cast<float*>(realloc(v, 4 * num_v * sizeof(float)));
        f = reinterpret_cast<Face*>(realloc(f, num_f * sizeof(Face)));
        n = new float[3 * num_f];
    }

    void Primitive::calculateNormals() {
        for (int i = 0; i < this->num_f; i++) {
            const auto& face = this->f[i];
            const auto* v1 = this->getVertex(face.v1);
            const auto* v2 = this->getVertex(face.v2);
            const auto* v3 = this->getVertex(face.v3);

            JTX::Util::Vec3 e1(v2[0] - v1[0], v2[1] - v1[1], v2[2] - v1[2]);
            JTX::Util::Vec3 e2(v3[0] - v1[0], v3[1] - v1[1], v3[2] - v1[2]);

            JTX::Util::Vec3 normal = e1.cross(e2).normalize();

            this->n[3 * i] = normal.x;
            this->n[3 * i + 1] = normal.y;
            this->n[3 * i + 2] = normal.z;
        }
    }

    void Primitive::applyTransform(const JTX::Util::Mat4* tf) {
        auto* new_v = new float[4 * num_v];
        cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasTrans, num_v, 4, 4, 1.0f,
                    v, 4, reinterpret_cast<const float*>(tf->data), 4, 0.0f, new_v, 4);
        delete[] v;
        v = new_v;
    }

    const float* Primitive::getVertex(int i) const {
        return v + 4 * i;
    }

    int Primitive::getNumVertices() const {
        return num_v;
    }

    const Face* Primitive::getFaces() const {
        return f;
    }

    int Primitive::getNumFaces() const {
        return num_f;
    }

    const float *Primitive::getNormal(int i) const {
        return n + (3 * i);
    }
} // JTX