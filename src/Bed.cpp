#include "Bed.h"

#include "Cube.h"
#include "Cylinder.h"

Bed::Bed(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float angle)
    : Object(pos, rot, scl, angle)
{
    init();
}

Bed::Bed(glm::vec3 pos, float angle)
    : Object(pos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), angle)
{
    init();
}

void Bed::init() {

    // colchao
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.7f, 0.35f, 1.0f)
    ));

    // encosto
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.35f, -0.5f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(0.7f, 0.5f, 0.05f),
        -2.0f
    ));

    // pes
    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(0.3f, -0.19f, -0.45f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.05f, 0.1f, 0.05f),
        1.0f
    ));

    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(-0.3f, -0.19f, -0.45f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.05f, 0.1f, 0.05f),
        -1.0f
    ));

    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(0.3f, -0.19f, 0.45f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.05f, 0.1f, 0.05f),
        1.0f
    ));

    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(-0.3f, -0.19f, 0.45f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.05f, 0.1f, 0.05f),
        -1.0f
    ));


}

void Bed::draw(Shader &shader, glm::mat4 model) {

    model = glm::translate(model, position);
    model = glm::scale(model, scale);
    if (glm::length(rotation) > 0.0f)
        model = glm::rotate(model, glm::radians(angle), glm::normalize(rotation));

    for (auto &part : parts) {
        part->draw(shader, model);
    }
}
