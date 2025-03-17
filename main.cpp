#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include "src/Common.h"
#include "src/VertexBuffer.h"
#include "src/IndexBuffer.h"
#include "src/VertexBufferLayout.h"
#include "src/VertexArray.h"
#include "src/Shaders.h"
#include "src/Renderer.h"
#include "src/Texture.h"
#include "src/EventHandler.h"

using namespace std;

/// Global Variables
float width = 640.0f, height = 480.0f;
glm::mat4 model(1.0f);
glm::mat4 perspective = glm::perspective(glm::radians(45.0f), width/height, 0.1f, 10.0f);
glm::mat4 I(1.0f);
EventHandler eventHandler;


/// Functions
void moveRight() {
    model = glm::translate(glm::mat4(1.0f), glm::vec3(0.03f, 0, 0)) * model;
}
void moveLeft() {
    model = glm::translate(glm::mat4(1.0f), glm::vec3(-0.03f, 0, 0)) * model;
}
void moveUp() {
    model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.03f, 0)) * model;
}
void moveDown() {
    model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.03f, 0)) * model;
}
void moveForward() {
    model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.03f)) * model;
}
void moveBackward() {
    model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -0.03f)) * model;
}
// Key callback function
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  eventHandler.KeyCallback(window, key, scancode, action, mods);
}

int main() {

    if(!glfwInit()) { // 
        std::cerr << "Failed to initialize GLFW" << std::endl;
        exit(1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width, height, "Hello Triangle!", nullptr, nullptr);

    if(!window) {
        std::cerr << "Failed to create Window" << std::endl;
        glfwTerminate();
        exit(1);
    }

    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to load procedures" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        exit(1);
    }

    /// this create a vector of 4 elements
    // glm::vec4 vertex(1.0f, 5.0f, 1.0f, 1.0f);
    /// this create and identity matrix of 4x4
    // glm::mat4 model(1.0f);
    /// lets create an scalling matrix
    // glm::mat4 transform = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 4.0f, 0.5f));
    /// performing rotation
    // glm::mat4 transform = glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(1, 0, 0));
    /// translation
    // glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(1, -2, 0));


    // printMat4(transform);
    // printVec(transform * vertex);


    float pos = 0.0;
    float positionsBlock[] = {
        -0.5f + pos, -0.5f, -3.0f, 0.0f, 0.0f,// 0  
         0.5f + pos,  0.5f, -3.0f, 2.0f, 2.0f,// 1
         0.5f + pos, -0.5f, -3.0f, 2.0f, 0.0f,// 2
        -0.5f + pos,  0.5f, -3.0f, 0.0f, 2.0f// 3
    };
    
    pos = 0.0f;
    float positionsSlime[] = {
        -0.5f + pos, -0.5f, 0.0f, 0.0f,// 0  
         0.5f + pos,  0.5f, 2.0f, 2.0f,// 1
         0.5f + pos, -0.5f, 2.0f, 0.0f,// 2
        -0.5f + pos,  0.5f, 0.0f, 2.0f// 3
    };

    unsigned int indices[] = {
        0, 1, 2,
        0, 1, 3
    };
{
    GLCall(glEnable(GL_BLEND));
    GLCall(glEnable(GL_DEPTH_TEST));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    // this is for the moving slime
    VertexArray vaoSlime; // vertex array object
    VertexBuffer vboSlime(positionsSlime, sizeof(positionsSlime)); // vertex buffer object
    VertexBufferLayout vloSlime; // vertex layout object
    vloSlime.Push<float>(2);
    vloSlime.Push<float>(2);
    vaoSlime.AddBuffer(&vboSlime, &vloSlime);

    // this is for the bloc
    VertexArray vaoBlock; // vertex array object
    VertexBuffer vboBlock(positionsBlock, sizeof(positionsBlock)); // vertex buffer object
    VertexBufferLayout vloBlock; // vertex layout object
    vloBlock.Push<float>(3);
    vloBlock.Push<float>(2);    
    vaoBlock.AddBuffer(&vboBlock, &vloBlock);


    IndexBuffer* ibo = new IndexBuffer(indices, 6);

    Texture textureSlime("assets/textures/slime.png");
    Texture textureBlock("assets/textures/oak.png");

    Shader shader("assets/shaders/simple.vert", "assets/shaders/simple.frag");

    Renderer renderer;

    eventHandler.AddFunction('w', moveUp);
    eventHandler.AddFunction('d', moveRight);
    eventHandler.AddFunction('s', moveDown);
    eventHandler.AddFunction('a', moveLeft);
    eventHandler.AddFunction('j', moveForward);
    eventHandler.AddFunction('k', moveBackward);

    glfwSetKeyCallback(window, KeyCallback);

    while(!glfwWindowShouldClose(window)) {
        renderer.Clear();
        
        shader.Bind();
        shader.setUniformMat4("model", I);

        textureBlock.Bind();
        GLCall(renderer.Draw(vaoBlock, *ibo, shader, 0));
        textureBlock.UnBind();

        eventHandler.ExecuteFunctions();

        textureSlime.Bind(1);
        shader.Bind();
        shader.setUniformMat4("model", model);
        shader.setUniformMat4("perspective", perspective);
        GLCall(renderer.Draw(vaoSlime, *ibo, shader, 1));
        textureSlime.UnBind();
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    delete ibo;
}
    
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
