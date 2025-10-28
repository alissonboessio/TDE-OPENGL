#include "Sphere.h"
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <cmath>

Sphere::Sphere(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang,
               float radius, int stacks, int slices)
    : position(pos), rotation(rot), scale(scl), angle(ang),
      radius_(radius), stacks_(stacks), slices_(slices)
{
    buildMesh();
}

void Sphere::buildMesh() {
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    const float PI = 3.14159265358979323846f;
    const float TWO_PI = 6.283185307179586f;

    for (int i = 0; i <= stacks_; ++i) {
        float v = (float)i / stacks_;           // 0..1
        float phi = PI * (v - 0.5f);            // [-π/2 .. +π/2]
        float cosPhi = std::cos(phi);
        float sinPhi = std::sin(phi);

        for (int j = 0; j <= slices_; ++j) {
            float u = (float)j / slices_;       // 0..1
            float theta = u * TWO_PI;           // [0..2π]
            float cosTheta = std::cos(theta);
            float sinTheta = std::sin(theta);

            float x = radius_ * cosPhi * cosTheta;
            float y = radius_ * sinPhi;
            float z = radius_ * cosPhi * sinTheta;

            vertices.insert(vertices.end(), { x, y, z, u, v });
        }
    }

    int stride = slices_ + 1;
    for (int i = 0; i < stacks_; ++i) {
        for (int j = 0; j < slices_; ++j) {
            int i0 =  i      * stride + j;
            int i1 =  i      * stride + j + 1;
            int i2 = (i + 1) * stride + j + 1;
            int i3 = (i + 1) * stride + j;

            indices.insert(indices.end(), { (unsigned)i0, (unsigned)i1, (unsigned)i2 });
            indices.insert(indices.end(), { (unsigned)i0, (unsigned)i2, (unsigned)i3 });
        }
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

    //Atributos: location 0 = pos(3), 1 = uv(2)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void Sphere::draw(Shader& shader, glm::mat4 model) {
    model = glm::translate(model, position);
    if (glm::length(rotation) > 0.0f)
        model = glm::rotate(model, glm::radians(angle), glm::normalize(rotation));
    model = glm::scale(model, scale);

    shader.setMat4("model", model);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

