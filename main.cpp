#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <string>
#include <fstream>

#include "assets/Common.h"
#include "assets/VertexBuffer.h"
#include "assets/IndexBuffer.h"

using namespace std;

static unsigned int CompileShader(unsigned int type, const std::string& source) {

    unsigned int id = glCreateShader(type); // create an id for the source
    const char* src = source.c_str(); // get a pointer to the source code

    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    // TODO: check for errors
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* msg = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, msg);
        
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment" ) << "Shader" << std::endl;
        std::cout << msg << std::endl;

        glDeleteShader(id);
        return 0;
    }

    return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragShader) {

    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragShader);

    glAttachShader(program, vs); // todo: better move it to the CompileShader function
    glAttachShader(program, fs);

    glLinkProgram(program);
    glValidateProgram(program);

    // Check for validation errors
    int validateStatus;
    glGetProgramiv(program, GL_VALIDATE_STATUS, &validateStatus);
    if (validateStatus == GL_FALSE) {
        int length;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
        char* msg = (char*)alloca(length * sizeof(char));
        glGetProgramInfoLog(program, length, &length, msg);
        
        std::cout << "Failed to validate program" << std::endl;
        std::cout << msg << std::endl;
    }

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

void increment(float & num, float amount) {
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
        -2.5f, -0.5f, // 0  
        -1.5f,  0.5f, // 1
        -1.5f, -0.5f, // 2
        -2.5f,  0.5f  // 3
    };

    unsigned int indices[] = {
        0, 1, 2,
        0, 1, 3
    };

    unsigned int vao;
    GLCall(glGenVertexArrays(1, &vao))
    GLCall(glBindVertexArray(vao))

    VertexBuffer* vbo = new VertexBuffer(positions, 4 * 2 * sizeof(float));

    GLCall(glEnableVertexAttribArray(0));
    GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0));

    IndexBuffer* ibo = new IndexBuffer(indices, 6);

    ifstream file("assets/shaders/simple.vert");
	string vertexShader = string(istreambuf_iterator<char>(file), istreambuf_iterator<char>());

    ifstream file2("assets/shaders/simple.frag");
	string fragmentShader = string(istreambuf_iterator<char>(file2), istreambuf_iterator<char>());

    unsigned int shader = CreateShader(vertexShader, fragmentShader);
    GLCall(glUseProgram(shader))

    GLCall(int uColor = glGetUniformLocation(shader, "u_Color"));
    ASSERT(uColor != -1)
    float red = 0.0f, green = 0.0f, blue = 0.0f;


    while(!glfwWindowShouldClose(window)) {
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
        
        for(int i = 0; i < 8; i+=2) positions[i] += 0.01;
        GLCall(glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), positions, GL_STATIC_DRAW));

        increment(red, 0.01f);
        increment(green, 0.002f);
        increment(blue, 0.03f);
        GLCall(glUniform4f(uColor, red, green, blue, 1.0f));

        GLCall(glUseProgram(shader));
        // glBindVertexArray(vao);

        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteProgram(shader);
    glDeleteVertexArrays(1, &vao);

    delete vbo;
    delete ibo;
    
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
