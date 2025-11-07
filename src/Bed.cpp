#include "Bed.h"

#include "Cube.h"
#include "Cylinder.h"

Bed::Bed(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float angle)
    : Object(pos, rot, scl, angle)
{
    setTextures();
    init();
}

Bed::Bed(glm::vec3 pos, float angle)
    : Object(pos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), angle)
{
    setTextures();
    init();
}

void Bed::setTextures() {
    texColchao = TextureManager::load("colchao.jpeg");
    texCorpo = TextureManager::load("lencolamassado.jpg");
    texCabeceira = TextureManager::load("madeira2.jpg");
    texPes = TextureManager::load("plasticopreto.jpeg");
}

void Bed::init() {
    parts.clear();

    // corpo
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.7f, 0.35f, 1.0f),
        0.0f,
        texColchao
    ));

    // colchao
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.175f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.7f, 0.005f, 1.0f),
        0.0f,
        texCorpo
    ));

    // cabeceira
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.35f, -0.5f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(0.7f, 0.5f, 0.05f),
        -2.0f,
        texCabeceira
    ));

    // pes
    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(0.3f, -0.19f, -0.45f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.05f, 0.1f, 0.05f),
        1.0f,
        texPes
    ));

    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(-0.3f, -0.19f, -0.45f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.05f, 0.1f, 0.05f),
        -1.0f,
        texPes
    ));

    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(0.3f, -0.19f, 0.45f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.05f, 0.1f, 0.05f),
        1.0f,
        texPes
    ));

    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(-0.3f, -0.19f, 0.45f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.05f, 0.1f, 0.05f),
        -1.0f,
        texPes
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
