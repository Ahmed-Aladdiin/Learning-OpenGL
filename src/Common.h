#pragma once

#include <assert.h>

#define ASSERT(x) if(!(x)) assert(false);
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);