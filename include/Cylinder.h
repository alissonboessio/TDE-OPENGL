#pragma once
#include <glm/glm.hpp>
#include "Shader.h"
#include "Object.h"

class Cylinder: public Object {
public:
    //height: extensão em Y (de -height/2 a +height/2)
    //radius: raio no plano XZ
    //segments: resolução angular (32 padrão)
    Cylinder(glm::vec3 pos = glm::vec3(0.0f),
             glm::vec3 rot = glm::vec3(0.0f, 1.0f, 0.0f),
             glm::vec3 scl = glm::vec3(1.0f),
             float angle = 0.0f,
             float height = 1.0f,
             float radius = 0.5f,
             int segments = 32);

    void draw(Shader& shader, glm::mat4 model);

    glm::vec3 position;
    glm::vec3 rotation; //eixo
    glm::vec3 scale;
    float angle;

private:
    unsigned int VAO = 0, VBO = 0, EBO = 0;
    int indexCount = 0;

    float height_, radius_;
    int segments_;

    void buildMesh();
};

