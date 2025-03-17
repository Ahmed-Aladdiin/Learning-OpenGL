#include "Common.h"
#include <iostream>
#include <glad/glad.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <gtx/string_cast.hpp>

void GLClearError() {
  while(glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line) {
  while(GLenum error = glGetError()) {
      std::cout << "(GL error) {"<< error << "}" << std::endl <<
      "In file: " << file << std::endl <<
      "Calling function: " << function << std::endl <<
      "At line: " << line << std::endl;
      return false;
  }
  return true;
}

inline void increment(float & num, float amount) {
    num += amount;  
    if (num > 1.0f) num -= 1;
}

void printMat4(glm::mat4 mat) {
    std::cout << glm::to_string(mat[0]) << std::endl;
    std::cout << glm::to_string(mat[1]) << std::endl;
    std::cout << glm::to_string(mat[2]) << std::endl;
    std::cout << glm::to_string(mat[3]) << std::endl;
}

template <typename T>
void printVec(T vec) {
    std::cout << glm::to_string(vec) << std::endl;
}