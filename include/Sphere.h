#pragma once
#include <glm/glm.hpp>
#include "Shader.h"
#include "Object.h"

class Sphere: public Object {
public:
    //radius: raio; stacks: “latitudes”; slices: “longitudes”
    Sphere(glm::vec3 pos = glm::vec3(0.0f),
           glm::vec3 rot = glm::vec3(0.0f, 1.0f, 0.0f),
           glm::vec3 scl = glm::vec3(1.0f),
           float angle = 0.0f,
           float radius = 1.0f,
           int stacks = 32,
           int slices = 48);

    void draw(Shader& shader, glm::mat4 model);

    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    float angle;

private:
    unsigned int VAO = 0, VBO = 0, EBO = 0;
    int indexCount = 0;
    float radius_;
    int stacks_, slices_;

    void buildMesh();
};

