#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Shader.h>
#include <Application.h>
#include <Cube.h>
#include <Banrisul.h>
#include <Texture.h>
#include <Prism.h>
#include <Cylinder.h>
#include <Sphere.h>
#include <Table.h>
#include <Chair.h>

#include <iostream>

int main() {
    //Cria janela e inicializa OpenGL
    Application app(1024, 768, "Cena: Cubos + Prisma + Cilindro");
    if (!app.init()) return -1;  //depth test habilitado em Application::init()

    //Shader
    Shader shader("vertex.glsl", "fragment.glsl");
    shader.use();

    //Texturas
    Texture tex1("pedra-28.jpg");
    Texture tex2("opengl.png");  // PNG com alpha

    shader.setInt("texture1", 0);
    shader.setInt("texture2", 1);

    //Objetos base
    Cube cube2(glm::vec3(2.0f, 0.0f, -2.5f));
    Cube cube3(glm::vec3(-2.0f, 1.0f, -4.0f));
    Cube cube4(glm::vec3(-3.0f, -1.0f, 3.0f));
    Cube cube5(glm::vec3(-4.0f, 0.0f, 0.0f));

    Banrisul banri(glm::vec3(0.0f, 0.0f, 0.0f), 0.0f);
    banri.scale = glm::vec3(2.5f, 2.5f, 2.5f);


    Table table(glm::vec3(0.0f, -3.0f, 0.0f), 0.0f);
    table.scale = glm::vec3(2.5f);


    Chair chair(glm::vec3(0.0f, 3.0f, 0.0f), 0.0f);
    chair.scale = glm::vec3(2.5f);



    //Prisma
    TriangularPrism prism(glm::vec3(3.0f, 0.0f, -4.0f));
    prism.scale    = glm::vec3(2.0f);
    prism.rotation = glm::vec3(0.0f, 1.0f, 0.0f);
    prism.angle    = 0.0f;

    //
    Cylinder cyl(
        glm::vec3(-1.5f, 0.0f, -5.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(2.0f),
        0.0f,
        1.0f,
        0.5f,
        48
    );

    Sphere sphere(
        glm::vec3(0.0f, 0.0f, -6.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(2.0f),
        0.0f,
        0.5f,
        32,
        48
    );

    //Loop principal
    while (!glfwWindowShouldClose(app.getWindow())) {
        //Input
        if (glfwGetKey(app.getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(app.getWindow(), true);

        //Limpa tela e depth buffer
        glClearColor(0.7f, 0.5f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();

        //Model base com rotação leve global
        glm::mat4 model = glm::mat4(1.0f);
        /*float angle = 20.0f;
        model = glm::rotate(model,
                            (angle * (float)glfwGetTime()) / 20.0f,
                            glm::vec3(0.0f, 0.3f, 0.0f));*/
        shader.setMat4("model", model);

        //View e Projection
        glm::mat4 projection = glm::perspective(glm::radians(45.0f),
                                                800.0f / 600.0f,
                                                0.1f, 100.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f),
                                        glm::vec3(0.0f, -0.0f, -15.0f));
        shader.setMat4("projection", projection);
        shader.setMat4("view", view);

        //Texturas
        tex1.bind(0);
        tex2.bind(1);

        // --------- Desenho ---------

        table.draw(shader, model);
        chair.draw(shader, model);

        /*
        //Prisma
        {
            glm::mat4 m = glm::rotate(model,
                                      (angle * (float)glfwGetTime()) / 30.0f,
                                      glm::vec3(0.0f, 1.0f, 0.0f));
            prism.draw(shader, m);
        }

        //Cilindro, tem uma rotação aplicada nele
        {
            glm::mat4 m = glm::rotate(glm::mat4(1.0f),
                                      (angle * (float)glfwGetTime()) / 25.0f,
                                      glm::vec3(0.0f, 1.0f, 0.0f));
            cyl.rotation = glm::vec3(1.0f, 0.0f, 0.0f); // eixo X
            cyl.angle = -20.0f;
            cyl.draw(shader, m);
        }

        //Esfera
        {
           glm::mat4 mS = glm::rotate(glm::mat4(1.0f),
                           (20.0f * (float)glfwGetTime()) / 22.0f,
                           glm::vec3(0.0f, 1.0f, 0.0f));
            sphere.draw(shader, mS);
        }
/*
      //CUBOS
        glm::mat4 m = model;

        m = glm::rotate(m, (angle * (float)glfwGetTime()) / 20.0f,
                        glm::vec3(0.5f, -0.2f, 0.5f));
        shader.setMat4("model", m);
        cube2.draw(shader, m);

        m = glm::rotate(m, (angle * (float)glfwGetTime()) / 5.0f,
                        glm::vec3(1.5f, 4.2f, 0.1f));
        shader.setMat4("model", m);
        cube3.draw(shader, m);

        m = glm::rotate(m, (-angle * (float)glfwGetTime()) / 40.0f,
                        glm::vec3(-0.8f, 2.1f, -2.0f));
        shader.setMat4("model", m);
        cube4.draw(shader, m);

        m = glm::rotate(m, (angle * (float)glfwGetTime()) / 40.0f,
                        glm::vec3(-0.5f, -0.2f, 1.45f));
        shader.setMat4("model", m);
        cube4.draw(shader, m);

        m = glm::mat4(1.0f);
        m = glm::rotate(m, (angle * (float)glfwGetTime()) / -40.0f,
                        glm::vec3(0.0f, 1.0f, 0.0f));
        cube5.draw(shader, m);
*/
        // Swap buffers e eventos
        glfwSwapBuffers(app.getWindow());
        glfwPollEvents();

    }

    return 0;
}
