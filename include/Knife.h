#ifndef KNIFE_H
#define KNIFE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Object.h"
#include "Shader.h"
#include <vector>
#include <memory>

class Knife: public Object{
public:

    Knife(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang);
    Knife(glm::vec3 pos, float ang);

    std::shared_ptr<Texture> texCorpo;

    void init();
    void setTextures();
    void draw(Shader &shader, glm::mat4 model);

private:

    std::vector<std::unique_ptr<Object>> parts;
};


#endif // KNIFE_H
