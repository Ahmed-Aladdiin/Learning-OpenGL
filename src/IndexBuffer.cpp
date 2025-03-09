#include "IndexBuffer.h"
#include <glad/glad.h>
#include "Common.h"

IndexBuffer::IndexBuffer(const unsigned int *data, unsigned int count) : m_count(count)
{
  ASSERT(sizeof(unsigned int) == sizeof(GLuint));

  GLCall(glGenBuffers(1, &m_RendererID));
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
  GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
  GLCall(glDeleteBuffers(1, &m_RendererID));
}

void IndexBuffer::Bind()
{
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void IndexBuffer::UnBind()
{
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
