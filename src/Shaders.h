#pragma once
#include <iostream>
#include <unordered_map>
#include <glm.hpp>

class Shader {
private:
  unsigned int m_RendererID;
  std::unordered_map<std::string, int> cachedUniforms;
public: 
  Shader(const std::string& vsPath, const std::string& fsPath);
  ~Shader();

  void Bind();
  void UnBind();

  void setUniform4f(const std::string& uniformName, float r, float g, float b, float a);
  void setUniform1i(const std::string& uniformName, int r);
  void setUniformMat4(const std::string &uniformName, glm::mat4 &mat);
  void setUniform3f(const std::string &uniformName, float r, float g, float b);
private:
  unsigned int CreateShader(const std::string vertexShader, const std::string fragShader);
  unsigned int CompileShader(unsigned int type, const std::string source);
  int getUniform(const std::string& uniformName);
};