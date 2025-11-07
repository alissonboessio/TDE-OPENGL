#ifndef FORK_H
#define FORK_H


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Object.h"
#include "Shader.h"
#include <vector>
#include <memory>

class Fork: public Object{
public:

    Fork(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang);
    Fork(glm::vec3 pos, float ang);

    std::shared_ptr<Texture> texCorpo;
    std::shared_ptr<Texture> texPegador;

    void init();
    void setTextures();
    void draw(Shader &shader, glm::mat4 model);

private:

    std::vector<std::unique_ptr<Object>> parts;
};


#endif // FORK_H
