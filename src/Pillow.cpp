#include "Pillow.h"

#include "Cube.h"
#include "Sphere.h"

Pillow::Pillow(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float angle)
    : Object(pos, rot, scl, angle)
{
    init();
}

Pillow::Pillow(glm::vec3 pos, float angle)
    : Object(pos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), angle)
{
    init();
}

void Pillow::init() {

    texTravesseiro = std::make_shared<Texture>("cetimmarrom.jpeg");

    parts.push_back(std::make_unique<Sphere>(
        glm::vec3(0.0f),
        glm::vec3(0.0f),
        glm::vec3(0.7f, 0.2f, 0.35f),
        0.0f,
        texTravesseiro
    ));

}

void Pillow::draw(Shader &shader, glm::mat4 model) {

    model = glm::translate(model, position);
    model = glm::scale(model, scale);
    if (glm::length(rotation) > 0.0f)
        model = glm::rotate(model, glm::radians(angle), glm::normalize(rotation));

    for (auto &part : parts) {
        part->draw(shader, model);
    }
}
