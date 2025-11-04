#include "Rack.h"

#include "Cube.h"
#include "Cylinder.h"
#include "Sphere.h"

Rack::Rack(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float angle)
    : Object(pos, rot, scl, angle)
{
    init();
}

Rack::Rack(glm::vec3 pos, float angle)
    : Object(pos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), angle)
{
    init();
}

void Rack::init() {

    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 1.0f, 0.7f)
    ));

    // pes
    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(0.4f, -0.5f, -0.25f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.05f, 0.3f, 0.05f),
        15.0f
    ));

    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(-0.4f, -0.5f, -0.25f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.05f, 0.3f, 0.05f),
        -15.0f
    ));

    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(0.4f, -0.5f, 0.25f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.05f, 0.3f, 0.05f),
        15.0f
    ));

    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(-0.4f, -0.5f, 0.25f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.05f, 0.3f, 0.05f),
        -15.0f
    ));

    // portas
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.25f, 0.35f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.9f, 0.45f, 0.05f)
    ));

    parts.push_back(std::make_unique<Sphere>(
        glm::vec3(0.0f, 0.25f, 0.40f),
        glm::vec3(0.0f),
        glm::vec3(1.0f),
        0.0f,
        0.05f
    ));

    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, -0.25f, 0.35f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.9f, 0.45f, 0.05f)
    ));

    parts.push_back(std::make_unique<Sphere>(
        glm::vec3(0.0f, -0.25f, 0.40f),
        glm::vec3(0.0f),
        glm::vec3(1.0f),
        0.0f,
        0.05f
    ));

}

void Rack::draw(Shader &shader, glm::mat4 model) {

    model = glm::translate(model, position);
    model = glm::scale(model, scale);
    if (glm::length(rotation) > 0.0f)
        model = glm::rotate(model, glm::radians(angle), glm::normalize(rotation));

    for (auto &part : parts) {
        part->draw(shader, model);
    }
}

