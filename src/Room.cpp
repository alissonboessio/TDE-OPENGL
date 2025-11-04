#include "Room.h"
#include "Cube.h"

Room::Room(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float angle)
    : Object(pos, rot, scl, angle)
{
    init();
}

Room::Room(glm::vec3 pos, float angle)
    : Object(pos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), angle)
{
    init();
}

void Room::init() {

    parts.push_back(std::make_unique<Cube>(
        glm::vec3(-0.5f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.05f, 1.0f, 1.0f)
    ));

    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.5f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.05f, 1.0f, 1.0f)
    ));

    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.0f, 0.475f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.95f, 1.0f, 0.05f)
    ));

    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.0f, -0.475f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.95f, 1.0f, 0.05f)
    ));

}

void Room::draw(Shader &shader, glm::mat4 model) {

    model = glm::translate(model, position);
    model = glm::scale(model, scale);
    if (glm::length(rotation) > 0.0f)
        model = glm::rotate(model, glm::radians(angle), glm::normalize(rotation));

    for (auto &part : parts) {
        part->draw(shader, model);
    }
}
