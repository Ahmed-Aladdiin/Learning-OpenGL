#include "Renderer.h"
#include "Common.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::Draw(VertexArray &va, IndexBuffer &ib, Shader &shader)
{
  va.Bind();
  ib.Bind();
  shader.Bind();
  
  GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear()
{
  GLCall(glClear(GL_COLOR_BUFFER_BIT));
}
