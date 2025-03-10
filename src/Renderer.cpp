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
  shader.setUniform1i("u_Texture", slot);
  
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

  va.UnBind();
  ib.UnBind();
  shader.UnBind();
}

void Renderer::Clear()
{
  GLCall(glClear(GL_COLOR_BUFFER_BIT));
}
