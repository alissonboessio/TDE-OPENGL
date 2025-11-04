#ifndef ROOM_H
#define ROOM_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Object.h"
#include "Shader.h"
#include <vector>
#include <memory>

class Room: public Object{
public:

    Room(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang);
    Room(glm::vec3 pos, float ang);

    void init();
    void draw(Shader &shader, glm::mat4 model);

private:

    std::vector<std::unique_ptr<Object>> parts;
};

#endif // ROOM_H
