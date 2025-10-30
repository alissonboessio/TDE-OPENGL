#include "Sofa.h"

#include "Cube.h"
#include "Cylinder.h"
#include "Sphere.h"

Sofa::Sofa(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float angle)
    : Object(pos, rot, scl, angle)
{
    init();
}

Sofa::Sofa(glm::vec3 pos, float angle)
    : Object(pos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), angle)
{
    init();
}

void Sofa::init() {

    // assento
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.35f, 0.6f)
    ));

    // encosto
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.35f, -0.25f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.5f, 0.15f),
        -10.0f
    ));

    // bracos
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(-0.425f, 0.2f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.15f, 0.1f, 0.55f)
    ));

    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(-0.425f, 0.25f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(0.15f, 0.55f, 0.15f),
        90.f
    ));

    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.425f, 0.2f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.15f, 0.1f, 0.55f)
    ));

    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(0.425f, 0.25f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(0.15f, 0.55f, 0.15f),
        90.f
    ));

    // pes
    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(0.4f, -0.1f, -0.25f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.05f, 0.3f, 0.05f),
        15.0f
    ));

    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(-0.4f, -0.1f, -0.25f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.05f, 0.3f, 0.05f),
        -15.0f
    ));

    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(0.4f, -0.1f, 0.25f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.05f, 0.3f, 0.05f),
        15.0f
    ));

    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(-0.4f, -0.1f, 0.25f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.05f, 0.3f, 0.05f),
        -15.0f
    ));


}

void Sofa::draw(Shader &shader, glm::mat4 model) {

    model = glm::translate(model, position);
    model = glm::scale(model, scale);

    for (auto &part : parts) {
        part->draw(shader, model);
    }
}
