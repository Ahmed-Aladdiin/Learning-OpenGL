#include "VertexBufferLayout.h"
#include <iostream>
#include <glad/glad.h>

template<>
void VertexBufferLayout::Push<float>(unsigned int count) {
  VertexBufferElement element = {GL_FLOAT, count, GL_FALSE};
  m_Elements.push_back(element);
  m_stride += VertexBufferElement::GetElementSize(GL_FLOAT) * count;
}

template<>
void VertexBufferLayout::Push<unsigned int>(unsigned int count) {
  m_Elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
  m_stride += VertexBufferElement::GetElementSize(GL_UNSIGNED_INT) * count;
}

template<>
void VertexBufferLayout::Push<unsigned char>(unsigned int count) {
  m_Elements.push_back({GL_UNSIGNED_BYTE, count, GL_FALSE});
  m_stride += VertexBufferElement::GetElementSize(GL_UNSIGNED_BYTE) * count;
}

VertexBufferLayout::VertexBufferLayout() : m_stride(0)
{
  m_Elements.clear();
}
