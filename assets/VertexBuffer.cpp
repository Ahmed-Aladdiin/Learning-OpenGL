#include "VertexBuffer.h"
#include <glad/glad.h>
#include "Common.h"

VertexBuffer::VertexBuffer(const void *data, int size)
{
  GLCall(glGenBuffers(1, &m_RendererID));
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
  GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
  GLCall(glDeleteBuffers(1, &m_RendererID));
}

void VertexBuffer::Bind()
{
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::UnBind()
{
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
