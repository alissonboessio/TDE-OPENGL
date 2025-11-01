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
#include <Television.h>
#include <Rack.h>
#include <Sofa.h>
#include <Fork.h>
#include <Knife.h>
#include <Bed.h>
#include <Pillow.h>

#include <iostream>

glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  20.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
float yaw        = -90.0f;
float pitch      = 0.0f;
float sensitivity= 0.2f;

void viraCamera(float x, float y) {
    yaw   += x * sensitivity;
    pitch += y * sensitivity;

    if (pitch > 89.0f)  pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
}

// velocidade dependente de deltaTime
void processInput(GLFWwindow* window, float deltaTime) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    const float cameraSpeed = 5.0f * deltaTime;

    // Caminhar (WASD)
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

    // Subir/Descer (Q/Z)
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        cameraPos += glm::vec3(0.0f, 1.0f, 0.0f) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        cameraPos += glm::vec3(0.0f, -1.0f, 0.0f) * cameraSpeed;

    // Olhar ao redor (setas)
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        viraCamera(0.0f,  1.0f);
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        viraCamera(0.0f, -1.0f);
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        viraCamera(-1.0f, 0.0f);
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        viraCamera( 1.0f, 0.0f);

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        cameraPos   = glm::vec3(0.0f, 0.0f, 20.0f);
        cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
        cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);
        yaw         = -90.0f;
        pitch       = 0.0f;
    }
}
// ================================================================

int main() {
    //Cria janela e inicializa OpenGL
    Application app(1024, 768, "Cena: Cubos + Prisma + Cilindro");
    if (!app.init()) return -1;  //depth test habilitado em Application::init()

    float lastTime = glfwGetTime();

    //Shader
    Shader shader("vertex.glsl", "fragment.glsl");
    shader.use();

    //Texturas
    Texture tex1("pedra-28.jpg");
    Texture tex2("opengl.png");  // PNG com alpha

    shader.setInt("texture1", 0);
    shader.setInt("texture2", 1);


    Table table(glm::vec3(0.0f, -3.0f, 0.0f), 0.0f);
    table.scale = glm::vec3(2.5f);


    Chair chair(glm::vec3(0.0f, 3.0f, 0.0f), 0.0f);
    chair.scale = glm::vec3(2.5f);

    Television television(glm::vec3(3.0f, 3.0f, 0.0f), 0.0f);
    television.scale = glm::vec3(2.5f);

    Rack rack(glm::vec3(-3.0f, 3.0f, 0.0f), 0.0f);
    rack.scale = glm::vec3(2.5f);

    Sofa sofa(glm::vec3(-3.0f, -3.0f, 0.0f), 0.0f);
    sofa.scale = glm::vec3(2.5f);

    Fork fork(glm::vec3(0.0f, 0.0f, 0.0f), 0.0f);
    fork.scale = glm::vec3(2.5f);

    Knife knife(glm::vec3(5.0f, 5.0f, 0.0f), 0.0f);
    knife.scale = glm::vec3(2.5f);

    Bed bed(glm::vec3(0.0f, 0.0f, 5.0f), 0.0f);
    bed.scale = glm::vec3(5.0f);

    Pillow pillow(glm::vec3(1.0f, 1.0f, 3.0f), 0.0f);
    pillow.scale = glm::vec3(1.0f);

    //Loop principal
    while (!glfwWindowShouldClose(app.getWindow())) {
        float now = glfwGetTime();
        float deltaTime = now - lastTime;
        lastTime = now;

        //Input
        if (glfwGetKey(app.getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(app.getWindow(), true);

        processInput(app.getWindow(), deltaTime);

        //Limpa tela e depth buffer
        glClearColor(0.7f, 0.5f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();

        //Model base com rotação leve global
        glm::mat4 model = glm::mat4(1.0f);
        float angle = 20.0f;
        /*model = glm::rotate(model,
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
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        shader.setMat4("view", view);

        //Texturas
        tex1.bind(0);
        tex2.bind(1);

        // --------- Desenho ---------

        // table.draw(shader, model);
        //chair.draw(shader, model);
        //television.draw(shader, model);
        //rack.draw(shader, model);
        //sofa.draw(shader, model);
        //fork.draw(shader, model);
        //knife.draw(shader, model);
        bed.draw(shader, model);
        pillow.draw(shader, model);

        // Swap buffers e eventos
        glfwSwapBuffers(app.getWindow());
        glfwPollEvents();

    }

    return 0;
}
