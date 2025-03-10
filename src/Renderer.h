#pragma once 

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shaders.h"

class Renderer
{
private:
  /* data */
public:
  Renderer();
  ~Renderer();

  void Draw(VertexArray& va, IndexBuffer& ib, Shader& shader, int slot);
  void Clear();
};
