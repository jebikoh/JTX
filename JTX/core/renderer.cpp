#include "renderer.h"
#include <iostream>

JTX::Core::Renderer::Renderer(int w, int h, int c) {
    if (w <= 0 || h <= 0 || c <= 0) {throw std::invalid_argument("Invalid dimensions");}

    this->w = w;
    this->h = h;
    this->c = c;
    this->ar = (float)w / (float)h;
    this->fb = new float[c * h * w]();
    this->zb = new float[h * w];

    for (int i = 0; i < w * h; i++) {this->zb[i] = 0.0f;}
}

void JTX::Core::Renderer::clear() {
    // TODO: SIMD
    std::memset(fb, 0.0f, c * h * w * sizeof(float));
    std::memset(zb, 0.0f, h * w * sizeof(float));
}

void JTX::Core::Renderer::render(JTX::Core::Scene *scene, ProjectionType projType) {
    // TODO: SIMD
    this->clear();
    JTX::Util::Mat4 t = scene->getCamera().getCameraMatrix(this->ar, projType);

    auto wf = static_cast<float>(this->w);
    auto hf = static_cast<float>(this->h);
    for (auto const & [id, prim] : scene->getPrimitives()) {
        prim->applyTransform(&t);

        for (int i = 0; i < prim->getNumVertices(); i++) {
            float *v = prim->getVertex(i);
            int *s = prim->getScreen(i);
            // NDC & Screen space transformation
            s[0] = static_cast<int>(std::round((v[0] / v[3] + 1.0f) * 0.5f * wf));
            s[1] = static_cast<int>(std::round((v[1] / v[3] + 1.0f) * 0.5f * hf));
            v[2] = (v[2] / v[3] + 1.0f) * 0.5f;
        }

        for (int i = 0; i < prim->getNumFaces(); i++) {
            float *n = prim->getNormal(i);

            // Back-face culling
            if (scene->getCamera().getLookAt().dot(n[0], n[1], n[2]) >= 0) {
                continue;
            }

            const Face *f = prim->getFace(i);
            int *v1 = prim->getScreen(f->v1);
            float z0 = prim->getVertex(f->v1)[2];

            int *v2 = prim->getScreen(f->v2);
            float z1 = prim->getVertex(f->v2)[2];

            int *v3 = prim->getScreen(f->v3);
            float z2 = prim->getVertex(f->v3)[2];

            // If the face is completely obscured, skip it
            if (z0 < this->getDepth(v1[0], v1[1]) ||
                z1 < this->getDepth(v2[0], v2[1]) ||
                z2 < this->getDepth(v3[0], v3[1])) {
                continue;
            }

            this->drawTriangle(
                    v1[0],
                    v1[1],
                    z0,
                    v2[0],
                    v2[1],
                    z1,
                    v3[0],
                    v3[1],
                    z2,
                    static_cast<float>(rand() % 255),
                    static_cast<float>(rand() % 255),
                    static_cast<float>(rand() % 255));
        }
    }
}

void JTX::Core::Renderer::renderWireframe(JTX::Core::Primitive &p, JTX::Util::Color color) {
    this->clear();
    auto w2 = 0.5f * static_cast<float>(this->w);
    auto h2 = 0.5f * static_cast<float>(this->h);

    // TODO: move this into the loop
    JTX::Util::Mat4 scale = JTX::Util::Mat4::scale(w2-1.0f, h2-1.0f, 1);
    JTX::Util::Mat4 trans = JTX::Util::Mat4::translation(w2, h2, 0);

    p.applyTransform(&scale);
    p.applyTransform(&trans);

    for (int i = 0; i < p.getNumFaces(); i++) {
        JTX::Core::Face *f = p.getFace(i);
        float *v1 = p.getVertex(f->v1);
        float *v2 = p.getVertex(f->v2);
        float *v3 = p.getVertex(f->v3);

        int v1_x = static_cast<int>(std::round(v1[0]));
        int v1_y = static_cast<int>(std::round(v1[1]));
        int v2_x = static_cast<int>(std::round(v2[0]));
        int v2_y = static_cast<int>(std::round(v2[1]));
        int v3_x = static_cast<int>(std::round(v3[0]));
        int v3_y = static_cast<int>(std::round(v3[1]));

        this->drawLine(v1_x, v1_y, v2_x, v2_y, color);
        this->drawLine(v2_x, v2_y, v3_x, v3_y, color);
        this->drawLine(v3_x, v3_y, v1_x, v1_y, color);
    }
}

void JTX::Core::Renderer::drawLine(int x0, int y0, int x1, int y1, float r, float g, float b) {
    if (x0 < 0 || x0 >= this->w || y0 < 0 || y0 >= this->h || x1 < 0 || x1 >= this->w || y1 < 0 || y1 >= this->h) {
        throw std::invalid_argument("Line out of bounds");
    }

    if (x0 == x1) {
        if (y0 > y1) {std::swap(y0, y1);}
        for (int y = y0; y <= y1; ++y) {
            drawPixel(x0, y, r, g, b);
        }
        return;
    }

    if (y0 == y1) {
        if (x0 > x1) {std::swap(x0, x1);}
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

void JTX::Core::Renderer::saveFb(const std::string &path, int compressionLevel) {
    if (this->c != 3) {throw std::invalid_argument("Invalid number of channels");}
    if (compressionLevel < 0 || compressionLevel > 9) {throw std::invalid_argument("Invalid compression level");}

    auto *pixels = new unsigned char[3 * this->w * this->h];

    for (int y = 0; y < this->h; ++y) {
        for (int x = 0; x < this->w; ++x) {
            for (int ch = 0; ch < this->c; ++ch) {
                float val = this->getPixel(x, y, ch);
                pixels[(y * this->w + x) * this->c + ch] = static_cast<unsigned char>(val);
            }
        }
    }
    bool success = fpng::fpng_encode_image_to_file(path.c_str(), pixels, this->w, this->h, this->c);

    if (success) {
        std::cout << "Image saved successfully: " << path << std::endl;
    } else {
        std::cerr << "Failed to save image: " << path << std::endl;
    }

    delete[] pixels;
}

void JTX::Core::Renderer::drawTriangle(int x0, int y0, float z0, int x1, int y1, float z1,  int x2, int y2, float z2, float r, float g, float b) {
    int minX = std::max(0, std::min(x0, std::min(x1, x2)));
    int minY = std::max(0, std::min(y0, std::min(y1, y2)));
    int maxX = std::min(this->w - 1, std::max(x0, std::max(x1, x2)));
    int maxY = std::min(this->h - 1, std::max(y0, std::max(y1, y2)));

    auto a = static_cast<float>(edgeFn(x0, y0, x1, y1, x2, y2));

    for (int y = minY; y <= maxY; ++y) {
        for (int x = minX; x <= maxX; ++x) {
            int w0 = edgeFn(x1, y1, x2, y2, x, y);
            int w1 = edgeFn(x2, y2, x0, y0, x, y);
            int w2 = edgeFn(x0, y0, x1, y1, x, y);

            // Ensure all signs are the same via XOR operation
            if ((w0 >= 0 && w1 >= 0 && w2 >= 0) || (w0 <= 0 && w1 <= 0 && w2 <= 0)) {
                float wz0 = static_cast<float>(w0) / a;
                float wz1 = static_cast<float>(w1) / a;
                float wz2 = static_cast<float>(w2) / a;
                float z = wz0 * z0 + wz1 * z1 + wz2 * z2;

                if (z < this->getDepth(x, y)) { continue; }

                this->setDepth(x, y, z);
                this->drawPixel(x, y, r, g, b);
            }
        }
    }
}

