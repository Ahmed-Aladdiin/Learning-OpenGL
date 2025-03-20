#include "Renderer.h"
#include "Common.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::Draw(VertexArray &va, IndexBuffer &ib, Shader &shader, int slot)
{
  va.Bind();
  ib.Bind();
  shader.Bind();
  
  glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);

  va.UnBind();
  ib.UnBind();
  shader.UnBind();
}

void Renderer::Clear()
{
  GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}
