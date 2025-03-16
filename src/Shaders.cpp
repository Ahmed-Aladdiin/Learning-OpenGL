#include "Shaders.h"

#include <iostream>
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <gtc/type_ptr.hpp>

Shader::Shader(const std::string& vsPath, const std::string& fsPath)
{
  std::ifstream vsFile(vsPath);
  std::ifstream fsFile(fsPath);

  if (!vsFile.is_open() || !fsFile.is_open()) {
    std::cerr << "Failed to open shader files" << std::endl;
    return;
  }

  std::string vertexShader = std::string(std::istreambuf_iterator<char>(vsFile), std::istreambuf_iterator<char>());
  std::string fragmentShader = std::string(std::istreambuf_iterator<char>(fsFile), std::istreambuf_iterator<char>());

  m_RendererID = CreateShader(vertexShader, fragmentShader);
}

Shader::~Shader()
{
  glDeleteProgram(m_RendererID);
}

void Shader::Bind()
{
  glUseProgram(m_RendererID);
}

void Shader::UnBind()
{
  glUseProgram(0);
}

void Shader::setUniform4f(const std::string &uniformName, float r, float g, float b, float a)
{
  glUniform4f(getUniform(uniformName), r, g, b, a);
}

void Shader::setUniform1i(const std::string &uniformName, int r)
{
  glUniform1i(getUniform(uniformName), r);
}

void Shader::setUniformMat4(const std::string &uniformName, glm::mat4 &mat)
{
  glUniformMatrix4fv(getUniform(uniformName), 1, GL_FALSE, glm::value_ptr(mat));
}

unsigned int Shader::CreateShader(const std::string vertexShader, const std::string fragShader)
{

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

unsigned int Shader::CompileShader(unsigned int type, const std::string source) {

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

int Shader::getUniform(const std::string &uniformName)
{
  if (cachedUniforms.find(uniformName) != cachedUniforms.end()) return cachedUniforms[uniformName];
  Bind();
  int uniformLoc = glGetUniformLocation(m_RendererID, uniformName.c_str());
  if (uniformLoc ==  -1) std::cout << "Uniform doesn't exist";
  cachedUniforms[uniformName] = uniformLoc;
  return uniformLoc;
}
