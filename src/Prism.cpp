
// Prism.cpp
#include "Prism.h"
#include <GL/glew.h>   // ou <GL/glew.h> dependendo do seu setup
#include <glm/gtc/matrix_transform.hpp>

// ---------------------------
// Vértices (pos3 + uv2)
// Definição com vértices duplicados por face (como no Cube):
//  - 2 faces triangulares  -> 3 vértices por face  =  6
//  - 3 faces retangulares  -> 4 vértices por face  = 12
// Total = 18 vértices; Índices = 8 triângulos (24 índices).
// Base no plano z=-0.5; Tampa em z=+0.5.
// Triângulo equilátero na base: A(-0.5,0), B(0.5,0), C(0,0.8660254)
// ---------------------------

// Prism.cpp — substitua SOMENTE este array:
static float prismVertices[] = {
    // ----- Tampa traseira (z = -0.5) - 1 tri  -----
    // Triângulo “deitado”: base no eixo X (A->B), altura no eixo Y (A->C)
    // Comprimentos: base = 1.2 (−0.6..+0.6), altura = 1.0 (0..1.0)
    // UV simples por tri: (0,0), (1,0), (0,1)
    -0.6f, 0.0f, -0.5f,   0.0f, 0.0f,   // 0  A
     0.6f, 0.0f, -0.5f,   1.0f, 0.0f,   // 1  B
    -0.6f, 1.0f, -0.5f,   0.0f, 1.0f,   // 2  C

    // ----- Tampa frontal (z = +0.5) - 1 tri -----
    // Mantemos o winding para frente (A', C', B')
    -0.6f, 0.0f,  0.5f,   0.0f, 0.0f,   // 3  A'
    -0.6f, 1.0f,  0.5f,   0.0f, 1.0f,   // 4  C'
     0.6f, 0.0f,  0.5f,   1.0f, 0.0f,   // 5  B'

    // ----- Lateral 1: AB–A'B' (base horizontal) → 2 tris -----
    // u ao longo de A→B (0..1), v ao longo de z (0..1)
    -0.6f, 0.0f, -0.5f,   0.0f, 0.0f,   // 6  A
     0.6f, 0.0f, -0.5f,   1.0f, 0.0f,   // 7  B
     0.6f, 0.0f,  0.5f,   1.0f, 1.0f,   // 8  B'
    -0.6f, 0.0f,  0.5f,   0.0f, 1.0f,   // 9  A'

    // ----- Lateral 2: BC–B'C' (face inclinada / hipotenusa) → 2 tris -----
    // u ao longo de B→C (0..1), v ao longo de z (0..1)
     0.6f, 0.0f, -0.5f,   0.0f, 0.0f,   // 10 B
    -0.6f, 1.0f, -0.5f,   1.0f, 0.0f,   // 11 C
    -0.6f, 1.0f,  0.5f,   1.0f, 1.0f,   // 12 C'
     0.6f, 0.0f,  0.5f,   0.0f, 1.0f,   // 13 B'

    // ----- Lateral 3: CA–C'A' (lateral vertical) → 2 tris -----
    // u ao longo de C→A (0..1), v ao longo de z (0..1)
    -0.6f, 1.0f, -0.5f,   0.0f, 0.0f,   // 14 C
    -0.6f, 0.0f, -0.5f,   1.0f, 0.0f,   // 15 A
    -0.6f, 0.0f,  0.5f,   1.0f, 1.0f,   // 16 A'
    -0.6f, 1.0f,  0.5f,   0.0f, 1.0f    // 17 C'
};


static unsigned int prismIndices[] = {
    // Tampas (2 tri)
    0, 1, 2,       // base (A,B, C)
    3, 4, 5,       // tampa (A',C',B')

    // Lateral 1 (AB–A'B') → (A,B,B') (A,B',A')
    6, 7, 8,
    6, 8, 9,

    // Lateral 2 (BC–B'C') → (B,C,C') (B,C',B')
    10, 11, 12,
    10, 12, 13,

    // Lateral 3 (CA–C'A') → (C,A,A') (C,A',C')
    14, 15, 16,
    14, 16, 17
};

TriangularPrism::TriangularPrism(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang)
    : position(pos), rotation(rot), scale(scl), angle(ang)
{
    init();
}

void TriangularPrism::init() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(prismVertices), prismVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(prismIndices), prismIndices, GL_STATIC_DRAW);

    // Atributos no mesmo layout do Cube: location 0 = pos (vec3), 1 = uv (vec2)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void TriangularPrism::draw(Shader &shader, glm::mat4 model) {
    model = glm::translate(model, position);

    if (glm::length(rotation) > 0.0f)
        model = glm::rotate(model, glm::radians(angle), glm::normalize(rotation));

    model = glm::scale(model, scale);
    shader.setMat4("model", model);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 8 * 3, GL_UNSIGNED_INT, 0); // 8 triângulos
    glBindVertexArray(0);
}
