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

    float positions[] = {
        -1.0f, -0.5f, 0.0f, 0.0f,// 0  
         0.0f,  0.5f, 1.0f, 1.0f,// 1
         0.0f, -0.5f, 1.0f, 0.0f,// 2
        -1.0f,  0.5f, 0.0f, 1.0f// 3
    };

    unsigned int indices[] = {
        0, 1, 2,
        0, 1, 3
    };
{
    VertexArray vao; // vertex array object
    VertexBuffer vbo(positions, 4 * 4 * sizeof(float)); // vertex buffer object
    VertexBufferLayout vlo; // vertex layout object
    vlo.Push<float>(2);
    vlo.Push<float>(2);
    vao.AddBuffer(&vbo, &vlo);

    IndexBuffer* ibo = new IndexBuffer(indices, 6);

    Texture texture("assets/textures/slime.png");
    texture.Bind();

    Shader shader("assets/shaders/simple.vert", "assets/shaders/simple.frag");
    GLCall(shader.Bind());
    shader.setUniform1i("u_Texture", 0);

    // float red = 0.0f, green = 0.0f, blue = 0.0f;
    // GLCall(shader.setUniform4f("u_Color", red, green, blue, 1.0f));

    Renderer renderer; 

    while(!glfwWindowShouldClose(window)) {
        renderer.Clear();

        for(int i = 0; i < 2*8; i+=4) positions[i] += 0.003;
        vbo.Update(positions, 4 * 4 * sizeof(float));

        // increment(red, 0.01f);
        // increment(green, 0.002f);
        // increment(blue, 0.03f);
        // GLCall(shader.setUniform4f("u_Color", red, green, blue, 1.0f));

        renderer.Draw(vao, *ibo, shader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    delete ibo;
}
    
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
