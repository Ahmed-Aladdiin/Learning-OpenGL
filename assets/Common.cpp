#include "Common.h"
#include <iostream>
#include <glad/glad.h>

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