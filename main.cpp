#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>

#include "assets/Common.h"
#include "assets/VertexBuffer.h"
#include "assets/IndexBuffer.h"
#include "assets/VertexBufferLayout.h"
#include "assets/VertexArray.h"
#include "assets/Shaders.h"

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

    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello Triangle!", nullptr, nullptr);

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

    float positions[] = {
        -1.5f, -0.5f, // 0  
        -0.5f,  0.5f, // 1
        -0.5f, -0.5f, // 2
        -1.5f,  0.5f  // 3
    };

    unsigned int indices[] = {
        0, 1, 2,
        0, 1, 3
    };
{
    VertexArray vao; // vertex array object
    VertexBuffer vbo(positions, 4 * 2 * sizeof(float)); // vertex buffer object
    VertexBufferLayout vlo; // vertex layout object
    vlo.Push<float>(2);
    vao.AddBuffer(&vbo, &vlo);

    IndexBuffer* ibo = new IndexBuffer(indices, 6);

    Shader shader("assets/shaders/simple.vert", "assets/shaders/simple.frag");
    GLCall(shader.Bind());

    float red = 0.0f, green = 0.0f, blue = 0.0f;
    GLCall(shader.setUniform4f("u_Color", red, green, blue, 1.0f));

    // vao.Bind();

    while(!glfwWindowShouldClose(window)) {
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
        
        for(int i = 0; i < 8; i+=2) positions[i] += 0.01;
        vbo.Update(positions, 4 * 2 * sizeof(float));

        increment(red, 0.01f);
        increment(green, 0.002f);
        increment(blue, 0.03f);
        GLCall(shader.setUniform4f("u_Color", red, green, blue, 1.0f));

        GLCall(shader.Bind());

        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    delete ibo;
}
    
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
