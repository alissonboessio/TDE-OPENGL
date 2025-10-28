#include "Cylinder.h"
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <cmath>

Cylinder::Cylinder(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang,
                   float height, float radius, int segments)
    : position(pos), rotation(rot), scale(scl), angle(ang),
      height_(height), radius_(radius), segments_(segments)
{
    buildMesh();
}

void Cylinder::buildMesh() {
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    vertices.reserve((segments_ + 1) * 4 * 5 + 2 * 5); //estimativa
    indices.reserve(segments_ * 12); //1 triangulo por face lateral + 2 triangulos por face retangular

    const float halfH = height_ * 0.5f;
    const float TWO_PI = 6.283185307179586f;

    int baseSide = 0;

    for (int ring = 0; ring < 2; ++ring) { // 0: bottom, 1: top
        float y = (ring == 0) ? -halfH : +halfH;
        float v = (ring == 0) ? 0.0f : 1.0f;

        for (int i = 0; i <= segments_; ++i) {
            float t = (i == segments_) ? TWO_PI : (float)i / segments_ * TWO_PI;
            float x = radius_ * std::cos(t);
            float z = radius_ * std::sin(t);
            float u = t / TWO_PI;

            vertices.insert(vertices.end(), { x, y, z, u, v });
        }
    }

    int stride = segments_ + 1;
    for (int i = 0; i < segments_; ++i) {
        int i0 = baseSide + i;
        int i1 = baseSide + i + 1;
        int i2 = baseSide + stride + i + 1;
        int i3 = baseSide + stride + i;

        //(i0, i1, i2) e (i0, i2, i3)
        indices.insert(indices.end(), { (unsigned)i0, (unsigned)i1, (unsigned)i2 });
        indices.insert(indices.end(), { (unsigned)i0, (unsigned)i2, (unsigned)i3 });
    }

    int centerBottomIndex = (int)(vertices.size() / 5);
    vertices.insert(vertices.end(), { 0.0f, -halfH, 0.0f, 0.5f, 0.5f });

    int ringBottomStart = (int)(vertices.size() / 5);
    for (int i = 0; i <= segments_; ++i) {
        float t = (i == segments_) ? TWO_PI : (float)i / segments_ * TWO_PI;
        float x = radius_ * std::cos(t);
        float z = radius_ * std::sin(t);
        float u = 0.5f + 0.5f * (x / radius_);
        float v = 0.5f + 0.5f * (z / radius_);
        vertices.insert(vertices.end(), { x, -halfH, z, u, v });
    }

    for (int i = 0; i < segments_; ++i) {
        indices.insert(indices.end(), {
            (unsigned)centerBottomIndex,
            (unsigned)(ringBottomStart + i + 1),
            (unsigned)(ringBottomStart + i)
        });
    }

    int centerTopIndex = (int)(vertices.size() / 5);
    vertices.insert(vertices.end(), { 0.0f, +halfH, 0.0f, 0.5f, 0.5f });

    int ringTopStart = (int)(vertices.size() / 5);
    for (int i = 0; i <= segments_; ++i) {
        float t = (i == segments_) ? TWO_PI : (float)i / segments_ * TWO_PI;
        float x = radius_ * std::cos(t);
        float z = radius_ * std::sin(t);
        float u = 0.5f + 0.5f * (x / radius_);
        float v = 0.5f + 0.5f * (z / radius_);
        vertices.insert(vertices.end(), { x, +halfH, z, u, v });
    }

    for (int i = 0; i < segments_; ++i) {
        indices.insert(indices.end(), {
            (unsigned)centerTopIndex,
            (unsigned)(ringTopStart + i),
            (unsigned)(ringTopStart + i + 1)
        });
    }

    indexCount = (int)indices.size();

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,
                 (GLsizeiptr)(vertices.size() * sizeof(float)),
                 vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 (GLsizeiptr)(indices.size() * sizeof(unsigned int)),
                 indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void Cylinder::draw(Shader& shader, glm::mat4 model) {
    model = glm::translate(model, position);
    if (glm::length(rotation) > 0.0f)
        model = glm::rotate(model, glm::radians(angle), glm::normalize(rotation));
    model = glm::scale(model, scale);

    shader.setMat4("model", model);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

