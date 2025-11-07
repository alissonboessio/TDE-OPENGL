#include "Object.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Object::Object()
    : position(0.0f), rotation(1.0f, 0.0f, 0.0f), scale(1.0f), angle(0.0f), tex(nullptr)
{}

Object::Object(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float angle, std::shared_ptr<Texture> tex)
    : position(pos), rotation(rot), scale(scl), angle(angle), tex(tex)
{
    // construtor básico — inicializa os valores recebidos
}

void Object::draw(Shader& shader, glm::mat4 parentTransform)
{
    // Implementação base vazia — serve para ser sobrescrita nas classes filhas
    // (Cube, Banrisul, etc.)

    // Exemplo: se quiser permitir que as classes derivadas chamem o comportamento padrão:
    // glm::mat4 model = parentTransform;
    // model = glm::translate(model, position);
    // model = glm::rotate(model, glm::radians(angle), rotation);
    // model = glm::scale(model, scale);
    // shader.setMat4("model", model);
}

void Object::setTextures()
{
}
