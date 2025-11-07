#ifndef DOOR_H
#define DOOR_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Object.h"
#include "Shader.h"
#include <vector>
#include <memory>

class Door: public Object{
public:

    Door(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang);
    Door(glm::vec3 pos, float ang);
    std::shared_ptr<Texture> tex;

    void init();
    void setTextures();
    void draw(Shader &shader, glm::mat4 model);

private:

    std::vector<std::unique_ptr<Object>> parts;
};

#endif // DOOR_H
