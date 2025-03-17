#pragma once

#include <assert.h>
#include <glm.hpp>

#define ASSERT(x) if(!(x)) assert(false);
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

inline void increment(float & num, float amount); 

void printMat4(glm::mat4 mat); 

template <typename T>
void printVec(T vec); 