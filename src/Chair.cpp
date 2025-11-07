#include "Chair.h"
#include "Cylinder.h"
#include "Cube.h"
#include "Sphere.h"


Chair::Chair(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float angle)
    : Object(pos, rot, scl, angle)
{
    setTextures();
    init();
}

Chair::Chair(glm::vec3 pos, float angle)
    : Object(pos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), angle)
{
    setTextures();
    init();
}

void Chair::setTextures() {
    texCorpo = TextureManager::load("madeira2.jpg");
    texAssento = TextureManager::load("palha.jpg");
}

void Chair::init() {
    parts.clear();

    //banco
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, -0.6f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.1f, 1.0f),
        0.0f,
        texAssento
    ));

    //pernas
    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(0.4f, -0.95f, 0.4f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.1f, 0.7f, 0.1f),
        0.0f,
        texCorpo
    ));

    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(0.4f, -0.95f, -0.4f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.1f, 0.7f, 0.1f),
        0.0f,
        texCorpo
    ));

    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(-0.4f, -0.95f, -0.4f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.1f, 0.7f, 0.1f),
        0.0f,
        texCorpo
    ));

    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(-0.4f, -0.95f, 0.4f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.1f, 0.7f, 0.1f),
        0.0f,
        texCorpo
    ));

    // encosto
    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(0.4f, -0.1f, -0.4f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.07f, 0.9f, 0.07f),
        0.0f,
        texCorpo
    ));

    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(-0.4f, -0.1f, -0.4f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.07f, 0.9f, 0.07f),
        0.0f,
        texCorpo
    ));


    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(0.0f, -0.25f, -0.4f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.07f, 0.8f, 0.07f),
        90.0f,
        texCorpo
    ));

    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(0.0f, 0.1f, -0.4f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.07f, 0.8f, 0.07f),
        90.0f,
        texCorpo
    ));

    parts.push_back(std::make_unique<Sphere>(
        glm::vec3(0.4f, 0.35f, -0.4f),
        glm::vec3(0.0f),
        glm::vec3(1.0f),
        0.0f,
        texCorpo,
        0.07f
    ));

    parts.push_back(std::make_unique<Sphere>(
        glm::vec3(-0.4f, 0.35f, -0.4f),
        glm::vec3(0.0f),
        glm::vec3(1.0f),
        0.0f,
        texCorpo,
        0.07f
    ));


}

void Chair::draw(Shader &shader, glm::mat4 model) {

    model = glm::translate(model, position);
    model = glm::scale(model, scale);
    if (glm::length(rotation) > 0.0f)
        model = glm::rotate(model, glm::radians(angle), glm::normalize(rotation));

    for (auto &part : parts) {
        part->draw(shader, model);
    }
}
