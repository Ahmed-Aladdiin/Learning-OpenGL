#include "VertexArray.h"
#include "Common.h"

#include <glad/glad.h>

VertexArray::VertexArray()
{
  GLCall(glGenVertexArrays(1, &m_RendererID));
}

VertexArray::~VertexArray()
{
  GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::AddBuffer(VertexBuffer *vb, VertexBufferLayout *layout)
{
  Bind();
  vb->Bind();
  const auto& elements = layout->GetElements();
  unsigned int offset = 0;
  for (unsigned int i = 0; i < elements.size(); i++) {
    const auto& element = elements[i];
    GLCall(glEnableVertexAttribArray(0));
    GLCall(glVertexAttribPointer(i, element.count, element.type, element.isNormalized, layout->GetStride(), (const void*) offset));
    offset += element.count * VertexBufferElement::GetElementSize(element.type);
  }
  
}

void VertexArray::Bind()
{
  GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::UnBind()
{
  GLCall(glBindVertexArray(0));
}
