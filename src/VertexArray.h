#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray {
private: 
  unsigned int m_RendererID;
public:
  VertexArray();
  ~VertexArray();

  void AddBuffer(VertexBuffer* vb, VertexBufferLayout* vbl);

  void Bind();
  void UnBind();
};