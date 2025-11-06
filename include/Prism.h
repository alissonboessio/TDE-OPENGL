#pragma once
#include <glm/glm.hpp>
#include "Shader.h"
#include <Object.h>

class TriangularPrism: Object {
public:
    TriangularPrism(glm::vec3 pos = glm::vec3(0.0f),
                    glm::vec3 rot = glm::vec3(0.0f, 1.0f, 0.0f),
                    glm::vec3 scl = glm::vec3(1.0f),
                    float angle = 0.0f,
                    std::shared_ptr<Texture> tex = nullptr);

    void draw(Shader &shader, glm::mat4 model);

    glm::vec3 position;
    glm::vec3 rotation; //eixo
    glm::vec3 scale;
    float angle;
    std::shared_ptr<Texture> tex;

private:
    unsigned int VAO = 0, VBO = 0, EBO = 0;
    void init();
};
