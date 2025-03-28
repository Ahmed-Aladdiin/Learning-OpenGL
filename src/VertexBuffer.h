#pragma once

class VertexBuffer {
private:
  unsigned int m_RendererID;
public:

  VertexBuffer(const void* data, int size);
  ~VertexBuffer();

  void Update(const void* data, int size);
  void Bind();
  void UnBind();
};