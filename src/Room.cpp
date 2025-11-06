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
    texChao = std::make_shared<Texture>("pisoquarto.jpg");
    texParede = std::make_shared<Texture>("paredebranca.jpg");

    parts.push_back(std::make_unique<Cube>(
        glm::vec3(-0.5f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.05f, 1.0f, 1.0f),
        0.0f,
        texParede
    ));

    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.5f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.05f, 1.0f, 1.0f),
        0.0f,
        texParede
    ));

    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.0f, 0.475f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.95f, 1.0f, 0.05f),
        0.0f,
        texParede
    ));

    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.0f, -0.475f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.95f, 1.0f, 0.05f),
        0.0f,
        texParede
    ));


    //chao
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, -0.5f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.005f, 1.0f),
        0.0f,
        texChao
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
