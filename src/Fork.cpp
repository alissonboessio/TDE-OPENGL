#include "Fork.h"
#include "Cube.h"

Fork::Fork(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float angle)
    : Object(pos, rot, scl, angle)
{
    init();
}

Fork::Fork(glm::vec3 pos, float angle)
    : Object(pos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), angle)
{
    init();
}

void Fork::init() {

    // corpo
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, -0.5f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.2f, 0.85f, 0.05f)
    ));

    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.55f, 0.15f, 0.05f)
    ));

    //dentes


    parts.push_back(std::make_unique<Cube>(
        glm::vec3(-0.225f, 0.35f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.1f, 0.55f, 0.05f)
    ));

    parts.push_back(std::make_unique<Cube>(
        glm::vec3(-0.075f, 0.35f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.1f, 0.55f, 0.05f)
    ));

    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.075f, 0.35f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.1f, 0.55f, 0.05f)
    ));


    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.225f, 0.35f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.1f, 0.55f, 0.05f)
    ));


}

void Fork::draw(Shader &shader, glm::mat4 model) {

    model = glm::translate(model, position);
    model = glm::scale(model, scale);
    if (glm::length(rotation) > 0.0f)
        model = glm::rotate(model, glm::radians(angle), glm::normalize(rotation));

    for (auto &part : parts) {
        part->draw(shader, model);
    }
}
