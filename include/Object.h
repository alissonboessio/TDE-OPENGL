#ifndef OBJECT_H
#define OBJECT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "Shader.h"
#include "Texture.h"
#include "TextureManager.h"
#include <memory>

class Object {
public:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    float angle;
    std::shared_ptr<Texture> tex;

    Object();
    Object(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang, std::shared_ptr<Texture> tex = nullptr);

    virtual void draw(Shader& shader, glm::mat4 parentTransform);
    virtual void setTextures();
    virtual ~Object() {}
};

#endif
