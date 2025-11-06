#ifndef PILLOW_H
#define PILLOW_H


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Object.h"
#include "Shader.h"
#include <vector>
#include <memory>

class Pillow: public Object{
public:

    Pillow(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang);
    Pillow(glm::vec3 pos, float ang);
    std::shared_ptr<Texture> texTravesseiro;

    void init();
    void draw(Shader &shader, glm::mat4 model);

private:

    std::vector<std::unique_ptr<Object>> parts;
};
#endif // PILLOW_H
