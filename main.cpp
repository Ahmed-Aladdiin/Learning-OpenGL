#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>

#include "src/Common.h"
#include "src/VertexBuffer.h"
#include "src/IndexBuffer.h"
#include "src/VertexBufferLayout.h"
#include "src/VertexArray.h"
#include "src/Shaders.h"
#include "src/Renderer.h"
#include "src/Texture.h"

using namespace std;

inline void increment(float & num, float amount) {
    num += amount;  
    if (num > 1.0f) num -= 1;
}

int main() {

    if(!glfwInit()) { // 
        std::cerr << "Failed to initialize GLFW" << std::endl;
        exit(1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(640, 640, "Hello Triangle!", nullptr, nullptr);

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

    float positionsBlock[] = {
        -0.5f, -0.5f, 0.0f, 0.0f,// 0  
         0.5f,  0.5f, 1.0f, 1.0f,// 1
         0.5f, -0.5f, 1.0f, 0.0f,// 2
        -0.5f,  0.5f, 0.0f, 1.0f// 3
    };
    
    float positionsSlime[] = {
        -1.5f, -0.5f, 0.0f, 0.0f,// 0  
        -0.5f,  0.5f, 1.0f, 1.0f,// 1
        -0.5f, -0.5f, 1.0f, 0.0f,// 2
        -1.5f,  0.5f, 0.0f, 1.0f// 3
    };

    unsigned int indices[] = {
        0, 1, 2,
        0, 1, 3
    };
{
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    // this is for the moving slime
    VertexArray vaoSlime; // vertex array object
    VertexBuffer vboSlime(positionsSlime, 4 * 4 * sizeof(float)); // vertex buffer object
    VertexBufferLayout vloSlime; // vertex layout object
    vloSlime.Push<float>(2);
    vloSlime.Push<float>(2);
    vaoSlime.AddBuffer(&vboSlime, &vloSlime);

    // this is for the bloc
    VertexArray vaoBlock; // vertex array object
    VertexBuffer vboBlock(positionsBlock, 4 * 4 * sizeof(float)); // vertex buffer object
    VertexBufferLayout vloBlock; // vertex layout object
    vloBlock.Push<float>(2);
    vloBlock.Push<float>(2);
    vaoBlock.AddBuffer(&vboBlock, &vloBlock);


    IndexBuffer* ibo = new IndexBuffer(indices, 6);

    Texture textureSlime("assets/textures/slime.png");
    Texture textureBlock("assets/textures/block.png");

    Shader shader("assets/shaders/simple.vert", "assets/shaders/simple.frag");

    Renderer renderer; 

    while(!glfwWindowShouldClose(window)) {
        renderer.Clear();

        for(int i = 0; i < 2*8; i+=4) positionsSlime[i] += 0.003;
        vboSlime.Update(positionsSlime, 4 * 4 * sizeof(float));

        textureBlock.Bind();
        GLCall(renderer.Draw(vaoBlock, *ibo, shader, 0));
        textureBlock.UnBind();

        textureSlime.Bind(1);
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
