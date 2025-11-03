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

    // Corpo
    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.9f, 0.5f, 0.9f)
    ));

    // Tampa
    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(0.0f, 0.2525f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.95f, 0.05f, 0.95f)
    ));

    parts.push_back(std::make_unique<Sphere>(
        glm::vec3(0.0f, 0.253f, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(1.0f),
        0.0f,
        0.08f
    ));

    // pegador
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.5f, 0.1f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.1f, 0.1f)
    ));

}

void Pot::draw(Shader &shader, glm::mat4 model) {

    model = glm::translate(model, position);
    model = glm::scale(model, scale);

    for (auto &part : parts) {
        part->draw(shader, model);
    }
}
