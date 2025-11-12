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
#include <Pot.h>
#include <Room.h>
#include <TextureManager.h>
#include <Door.h>

#include <iostream>

glm::vec3 cameraPos   = glm::vec3(-4.0f, 12.5f, 15.0f);
glm::vec3 cameraFront = glm::vec3(0.3f, 0.6f, -0.7f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);
float yaw        = -65.0f;
float pitch      = -40.0f;
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

    // Subir/Descer (Espaço/Shift Esquerdo)
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
        cameraPos   = glm::vec3(-4.0f, 12.5f, 15.0f);
        cameraFront = glm::vec3(0.3f, 0.6f, -0.7f);
        cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);
        yaw         = -65.0f;
        pitch       = -40.0f;
        viraCamera(0.0f, -1.0f);
    }

}
// ================================================================

int main() {
    //Cria janela e inicializa OpenGL
    Application app(1024, 768, "Planta Baixa");
    if (!app.init()) {
        return -1;
    }

    float lastTime = glfwGetTime();

    //Shader
    Shader shader("vertex.glsl", "fragment.glsl");
    shader.use();

    shader.setInt("texture1", 0);

    auto chaoMundo = std::make_unique<Cube>(
        glm::vec3(0.0f, -0.1f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(200.0f, 0.005f, 200.0f),
        0.0f,
        TextureManager::load("verde.jpeg")
    );

    Room room1(glm::vec3(3.0f, 2.5f, -3.0f), 0.0f);
    room1.scale = glm::vec3(5.0f);
    room1.texChao = TextureManager::load("piso-xadrez.jpg");
    room1.init();

    Door door1(glm::vec3(2.0f, 2.0f, -0.55f), 0.0f);
    door1.scale = glm::vec3(5.0f, 4.5f, 5.0f);

    Room room2(glm::vec3(-2.5f, 2.5f, 0.0f), 0.0f);
    room2.scale = glm::vec3(6.0f, 5.0f, 6.0f);

    Door door2(glm::vec3(0.5f, 2.0f, 1.15f), 90.0f);
    door2.rotation = glm::vec3(0.0f, 1.0f, 0.0f);
    door2.scale = glm::vec3(3.55f, 4.5f, 5.0f);

    Room room3(glm::vec3(3.75f, 2.5f, 3.25f), 0.0f);
    room3.scale = glm::vec3(6.5f, 5.0f, 8.0f);

    Door door3(glm::vec3(2.0f, 2.0f, 7.05f), 0.0f);
    door3.scale = glm::vec3(6.5f, 4.5f, 5.0f);

    // sala
    Rack rack1(glm::vec3(6.45f, 0.65f, 2.25f), -90.0f);
    rack1.scale = glm::vec3(1.0f);
    rack1.rotation = glm::vec3(0.0f, 1.0f, 0.0f);

    Rack rack2(glm::vec3(6.45f, 0.65f, 3.25f), -90.0f);
    rack2.scale = glm::vec3(1.0f);
    rack2.rotation = glm::vec3(0.0f, 1.0f, 0.0f);

    Rack rack3(glm::vec3(6.45f, 0.65f, 4.25f), -90.0f);
    rack3.scale = glm::vec3(1.0f);
    rack3.rotation = glm::vec3(0.0f, 1.0f, 0.0f);

    Television television(glm::vec3(6.6f, 2.0f, 3.25f), -90.0f);
    television.scale = glm::vec3(2.0f);
    television.rotation = glm::vec3(0.0f, 1.0f, 0.0f);

    Sofa sofa(glm::vec3(4.0f, 0.65f, 3.25f), 90.0f);
    sofa.scale = glm::vec3(2.5f);
    sofa.rotation = glm::vec3(0.0f, 1.0f, 0.0f);

    // quarto
    Bed bed(glm::vec3(-3.15f, 0.9f, 0.0f), 90.0f);
    bed.scale = glm::vec3(4.0f);
    bed.rotation = glm::vec3(0.0f, 1.0f, 0.0f);

    Pillow pillow1(glm::vec3(-4.65f, 1.7f, 0.7f), 90.0f);
    pillow1.scale = glm::vec3(0.9f);
    pillow1.rotation = glm::vec3(0.0f, 1.0f, 0.0f);

    Pillow pillow2(glm::vec3(-4.65f, 1.7f, -0.7f), 90.0f);
    pillow2.scale = glm::vec3(0.9f);
    pillow2.rotation = glm::vec3(0.0f, 1.0f, 0.0f);

    Pillow pillow3(glm::vec3(-4.25f, 1.75f, 0.0f), 90.0f);
    pillow3.scale = glm::vec3(0.9f);
    pillow3.rotation = glm::vec3(0.0f, 1.0f, 0.0f);

    Rack rackQuarto1(glm::vec3(-4.8f, 0.65f, 2.0f), 90.0f);
    rackQuarto1.scale = glm::vec3(0.8f);
    rackQuarto1.rotation = glm::vec3(0.0f, 1.0f, 0.0f);

    Rack rackQuarto2(glm::vec3(-4.8f, 0.65f, -2.0f), 90.0f);
    rackQuarto2.scale = glm::vec3(0.8f);
    rackQuarto2.rotation = glm::vec3(0.0f, 1.0f, 0.0f);

    // cozinha
    Table table(glm::vec3(3.0f, 0.9f, -3.0f), 0.0f);
    table.scale = glm::vec3(1.5f);

    Chair chair1(glm::vec3(3.0f, 1.4f, -4.0f), 0.0f);
    chair1.scale = glm::vec3(1.0f);

    Chair chair2(glm::vec3(3.0f, 1.4f, -2.0f), 180.0f);
    chair2.scale = glm::vec3(1.0f);
    chair2.rotation = glm::vec3(0.0f, 1.0f, 0.0f);

    Chair chair3(glm::vec3(4.0f, 1.4f, -3.0f), -90.0f);
    chair3.scale = glm::vec3(1.0f);
    chair3.rotation = glm::vec3(0.0f, 1.0f, 0.0f);

    Chair chair4(glm::vec3(2.0f, 1.4f, -3.0f), 90.0f);
    chair4.scale = glm::vec3(1.0f);
    chair4.rotation = glm::vec3(0.0f, 1.0f, 0.0f);

    Pot pot(glm::vec3(3.0f, 1.85f, -3.2f), 45.0f);
    pot.scale = glm::vec3(0.65f);
    pot.rotation = glm::vec3(0.0f, 1.0f, 0.0f);

    Fork fork1(glm::vec3(3.1f, 1.735f, -2.5f), -90.0f);
    fork1.scale = glm::vec3(0.1f);
    fork1.rotation = glm::vec3(1.0f, 0.0f, 0.0f);

    Fork fork2(glm::vec3(3.17f, 1.735f, -2.5f), -90.0f);
    fork2.scale = glm::vec3(0.1f);
    fork2.rotation = glm::vec3(1.0f, 0.0f, 0.0f);

    Fork fork3(glm::vec3(3.24f, 1.735f, -2.5f), -90.0f);
    fork3.scale = glm::vec3(0.1f);
    fork3.rotation = glm::vec3(1.0f, 0.0f, 0.0f);

    Fork fork4(glm::vec3(3.31f, 1.735f, -2.5f), -90.0f);
    fork4.scale = glm::vec3(0.1f);
    fork4.rotation = glm::vec3(1.0f, 0.0f, 0.0f);

    Knife knife1(glm::vec3(2.9f, 1.735f, -2.5f), -90.0f);
    knife1.scale = glm::vec3(0.1f);
    knife1.rotation = glm::vec3(1.0f, 0.0f, 0.0f);

    Knife knife2(glm::vec3(2.83f, 1.735f, -2.5f), -90.0f);
    knife2.scale = glm::vec3(0.1f);
    knife2.rotation = glm::vec3(1.0f, 0.0f, 0.0f);

    Knife knife3(glm::vec3(2.76f, 1.735f, -2.5f), -90.0f);
    knife3.scale = glm::vec3(0.1f);
    knife3.rotation = glm::vec3(1.0f, 0.0f, 0.0f);

    Knife knife4(glm::vec3(2.69f, 1.735f, -2.5f), -90.0f);
    knife4.scale = glm::vec3(0.1f);
    knife4.rotation = glm::vec3(1.0f, 0.0f, 0.0f);

    viraCamera(0.0f, -1.0f);
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
        glClearColor(0.529f, 0.808f, 0.922f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();

        glm::mat4 model = glm::mat4(1.0f);
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

        // --------- Desenho ---------

        chaoMundo->draw(shader, model);

        room1.draw(shader, model);
        door1.draw(shader, model);
        room2.draw(shader, model);
        door2.draw(shader, model);
        room3.draw(shader, model);
        door3.draw(shader, model);

        // sala
        television.draw(shader, model);
        rack1.draw(shader, model);
        rack2.draw(shader, model);
        rack3.draw(shader, model);
        sofa.draw(shader, model);

        // quarto
        bed.draw(shader, model);
        pillow1.draw(shader, model);
        pillow2.draw(shader, model);
        pillow3.draw(shader, model);
        rackQuarto1.draw(shader, model);
        rackQuarto2.draw(shader, model);

        // cozinha
        table.draw(shader, model);
        chair1.draw(shader, model);
        chair2.draw(shader, model);
        chair3.draw(shader, model);
        chair4.draw(shader, model);
        pot.draw(shader, model);
        fork1.draw(shader, model);
        fork2.draw(shader, model);
        fork3.draw(shader, model);
        fork4.draw(shader, model);
        knife1.draw(shader, model);
        knife2.draw(shader, model);
        knife3.draw(shader, model);
        knife4.draw(shader, model);

        // Swap buffers e eventos
        glfwSwapBuffers(app.getWindow());
        glfwPollEvents();

    }

    return 0;
}
