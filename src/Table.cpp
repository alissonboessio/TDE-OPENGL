#include "Table.h"
#include "Cube.h"
#include "Cylinder.h"

Table::Table(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float angle)
    : Object(pos, rot, scl, angle)
{
    setTextures();
    init();
}

Table::Table(glm::vec3 pos, float angle)
    : Object(pos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), angle)
{
    setTextures();
    init();
}

void Table::setTextures() {
    texTampo = TextureManager::load("marmore.jpg");
    texCorpo = TextureManager::load("madeira2.jpg");
}

void Table::init() {
    parts.clear();


    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(0.0f, 0.5f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.1f, 1.0f),
        0.0f,
        texTampo
    ));

    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.1f, 1.0f, 0.1f),
        0.0f,
        texCorpo
    ));

    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(0.0f, -0.5f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.4f, 0.1f, 0.4f),
        0.0f,
        texCorpo
    ));

}

void Table::draw(Shader &shader, glm::mat4 model) {

    model = glm::translate(model, position);
    model = glm::scale(model, scale);
    if (glm::length(rotation) > 0.0f)
        model = glm::rotate(model, glm::radians(angle), glm::normalize(rotation));

    for (auto &part : parts) {
        part->draw(shader, model);
    }
}
