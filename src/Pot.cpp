#include "Pot.h"

#include "Cylinder.h"
#include "Cube.h"
#include "Sphere.h"


Pot::Pot(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float angle)
    : Object(pos, rot, scl, angle)
{
    init();
}

Pot::Pot(glm::vec3 pos, float angle)
    : Object(pos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), angle)
{
    init();
}

void Pot::init() {

    texCorpo = std::make_shared<Texture>("aluminio.jpg");
    texPegador = std::make_shared<Texture>("madeira2.jpg");

    // Corpo
    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.9f, 0.5f, 0.9f),
        0.0f,
        texCorpo
    ));

    // Tampa
    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(0.0f, 0.2525f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.95f, 0.05f, 0.95f),
        0.0f,
        texCorpo
    ));

    parts.push_back(std::make_unique<Sphere>(
        glm::vec3(0.0f, 0.253f, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(1.0f),
        0.0f,
        texPegador,
        0.08f
    ));

    // pegador
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.5f, 0.1f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.1f, 0.1f),
        0.0f,
        texPegador
    ));

}

void Pot::draw(Shader &shader, glm::mat4 model) {

    model = glm::translate(model, position);
    model = glm::scale(model, scale);
    if (glm::length(rotation) > 0.0f)
        model = glm::rotate(model, glm::radians(angle), glm::normalize(rotation));

    for (auto &part : parts) {
        part->draw(shader, model);
    }
}
