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
#include "src/Camera.h"

using namespace std;

/// Global Variables
float width = 1280.0f, height = 720.0f;
glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -1.0f));
glm::mat4 rotation(1.0f);
glm::mat4 perspective = glm::perspective(glm::radians(45.0f), width/height, 0.1f, 10.0f);
glm::mat4 I(1.0f);
EventHandler eventHandler;


/// Functions
void moveRight() {
    translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.03f, 0, 0)) * translate;
}
void moveLeft() {
    translate = glm::translate(glm::mat4(1.0f), glm::vec3(-0.03f, 0, 0)) * translate;
}
void moveUp() {
    translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.03f, 0)) * translate;
}
void moveDown() {
    translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.03f, 0)) * translate;
}
void moveForward() {
    translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.03f)) * translate;
}
void moveBackward() {
    translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -0.03f)) * translate;
}
void rotateY() {
    rotation = glm::rotate(rotation, glm::radians(5.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}
void rotateX() {
    rotation = glm::rotate(rotation, glm::radians(5.0f), glm::vec3(1.0f, 0.0f, 0.0f));
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


    // float positionsBlock[] = {
    //     -0.5f + pos, -0.5f, -3.0f, 0.0f, 0.0f,// 0  
    //      0.5f + pos,  0.5f, -3.0f, 2.0f, 2.0f,// 1
    //      0.5f + pos, -0.5f, -3.0f, 2.0f, 0.0f,// 2
    //     -0.5f + pos,  0.5f, -3.0f, 0.0f, 2.0f// 3
    // };
    
    float positionsBlock[] = {
        // front face
        -0.5f,  0.5f,  0.5f, 0.334f, 0.75f,// 0 // top left  
         0.5f,  0.5f,  0.5f, 0.667f, 0.75f,// 1 // top right
         0.5f, -0.5f,  0.5f, 0.667f, 0.5f,// 2  // bottom right
        -0.5f, -0.5f,  0.5f, 0.334f, 0.5f,// 3  // bottom left

        // back face
        -0.5f,  0.5f, -0.5f, 0.334f, 0.0f,// 4 // top left  
         0.5f,  0.5f, -0.5f, 0.667f, 0.0f,// 5 // top right
         0.5f, -0.5f, -0.5f, 0.667f, 0.25f,// 6 // bottom right
        -0.5f, -0.5f, -0.5f, 0.334f, 0.25f,// 7 // bottom left

        // top face
        -0.5f,  0.5f,  0.5f, 0.667f, 0.75f,// 8  // near right
        -0.5f,  0.5f, -0.5f, 0.667f, 1.00f,// 9  // far right
         0.5f,  0.5f,  0.5f, 0.334f, 0.75f,// 10 // near left
         0.5f,  0.5f, -0.5f, 0.334f, 1.00f, // 11 // far left

        // bottom face
        -0.5f, -0.5f,  0.5f, 0.667f, 0.50f,// 12  // near right
        -0.5f, -0.5f, -0.5f, 0.667f, 0.25f,// 13 // far right
         0.5f, -0.5f,  0.5f, 0.334f, 0.50f,// 14 // near left
         0.5f, -0.5f, -0.5f, 0.334f, 0.25f,// 15 // far left
        
        // right face
         0.5f, -0.5f,  0.5f, 0.667f, 0.50f,// 16  // near bottom
         0.5f,  0.5f,  0.5f, 0.667f, 0.75f,// 17  // near up
         0.5f, -0.5f, -0.5f, 1.000f, 0.50f,// 18 // far  bottom
         0.5f,  0.5f, -0.5f, 1.000f, 0.75f,// 19 // far  up
        
        // left face
        -0.5f, -0.5f,  0.5f, 0.334f, 0.50f,// 20  // near bottom
        -0.5f,  0.5f,  0.5f, 0.334f, 0.75f,// 21  // near up
        -0.5f, -0.5f, -0.5f, 0.000f, 0.50f,// 22 // far  bottom
        -0.5f,  0.5f, -0.5f, 0.000f, 0.75f // 23 // far  up
    };
    
    unsigned int indices[] = {
        0, 1, 2, // front face
        0, 2, 3,

        4, 5, 6, // back face
        4, 6, 7,

        8, 9, 11, // top side 
        8, 11, 10,

        12, 13, 15, // bottom face
        12, 15, 14,

        16, 17, 19, // right face
        16, 19, 18,

        20, 21, 23, // left face
        20, 23, 22
    };
{
    GLCall(glEnable(GL_BLEND));
    GLCall(glEnable(GL_DEPTH_TEST));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    // this is for the bloc
    VertexArray vaoBlock; // vertex array object
    VertexBuffer vboBlock(positionsBlock, sizeof(positionsBlock)); // vertex buffer object
    VertexBufferLayout vloBlock; // vertex layout object
    vloBlock.Push<float>(3);
    vloBlock.Push<float>(2);    
    vaoBlock.AddBuffer(&vboBlock, &vloBlock);


    IndexBuffer* ibo = new IndexBuffer(indices, sizeof(indices)/sizeof(unsigned int));

    // Texture textureSlime("assets/textures/slime.png");
    Texture textureBlock("assets/textures/oak-texture.png");

    Shader shader("assets/shaders/simple.vert", "assets/shaders/simple.frag");

    Renderer renderer;
    Camera camera(glm::vec3(0, 0, 2), 0.1f, 100.0f, width, height);

    eventHandler.AddFunction(GLFW_KEY_W, moveUp);
    eventHandler.AddFunction(GLFW_KEY_D, moveRight);
    eventHandler.AddFunction(GLFW_KEY_S, moveDown);
    eventHandler.AddFunction(GLFW_KEY_A, moveLeft);

    eventHandler.AddFunction(GLFW_KEY_E, moveForward);
    eventHandler.AddFunction(GLFW_KEY_Q, moveBackward);

    eventHandler.AddFunction(GLFW_KEY_X, rotateY);
    eventHandler.AddFunction(GLFW_KEY_Z, rotateX);

    glfwSetKeyCallback(window, KeyCallback);

    while(!glfwWindowShouldClose(window)) {
        renderer.Clear();
        
        // shader.Bind();
        // shader.setUniformMat4("model", I);

        // textureBlock.Bind();
        // GLCall(renderer.Draw(vaoBlock, *ibo, shader, 0));
        // textureBlock.UnBind();

        eventHandler.ExecuteFunctions();
        camera.Inputs(window);

        glm::mat4 model = (translate * rotation);
        glm::mat4 view = camera.GetLookAtMat();
        textureBlock.Bind(1);
        shader.Bind();
        shader.setUniformMat4("model", model);
        shader.setUniformMat4("view", view);
        shader.setUniformMat4("perspective", perspective);
        GLCall(renderer.Draw(vaoBlock, *ibo, shader, 1));
        textureBlock.UnBind();
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    delete ibo;
}
    
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
