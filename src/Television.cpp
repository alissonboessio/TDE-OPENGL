#include "Television.h"

#include "Cube.h"
#include "Cylinder.h"

Television::Television(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float angle)
    : Object(pos, rot, scl, angle)
{
    init();
}

Television::Television(glm::vec3 pos, float angle)
    : Object(pos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), angle)
{
    init();
}

void Television::init() {
    texCorpo = std::make_shared<Texture>("plasticopreto.jpeg");
    texMonitor = std::make_shared<Texture>("monitor.jpg");

    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.7f, 0.1f),
        0.0f,
        texCorpo
    ));

    // monitor
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.0f, 0.0525f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.9f, 0.6f, 0.005f),
        0.0f,
        texMonitor
    ));

    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(0.4f, -0.35f, 0.0f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.05f, 0.3f, 0.05f),
        30.0f,
        texCorpo
    ));

    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(-0.4f, -0.35f, 0.0f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.05f, 0.3f, 0.05f),
        -30.0f,
        texCorpo
    ));

}

void Television::draw(Shader &shader, glm::mat4 model) {

    model = glm::translate(model, position);
    model = glm::scale(model, scale);
    if (glm::length(rotation) > 0.0f)
        model = glm::rotate(model, glm::radians(angle), glm::normalize(rotation));

    for (auto &part : parts) {
        part->draw(shader, model);
    }
}
