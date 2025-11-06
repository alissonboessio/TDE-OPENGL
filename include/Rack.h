#ifndef RACK_H
#define RACK_H


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Object.h"
#include "Shader.h"
#include <vector>
#include <memory>

class Rack: public Object{
public:

    Rack(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang);
    Rack(glm::vec3 pos, float ang);
    std::shared_ptr<Texture> texCorpo;
    std::shared_ptr<Texture> texPegador;
    std::shared_ptr<Texture> texPorta;

    void init();
    void draw(Shader &shader, glm::mat4 model);

private:

    std::vector<std::unique_ptr<Object>> parts;
};


#endif // RACK_H
