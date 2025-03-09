#pragma once

#include <vector>
#include <glad/glad.h>
#include "Common.h"

struct VertexBufferElement
{
  unsigned int type;
  unsigned int count;
  unsigned int isNormalized;

  static unsigned int GetElementSize(unsigned int type) {
    switch (type)
    {
    case GL_FLOAT:
      return sizeof(float);
    case GL_UNSIGNED_BYTE:
      return sizeof(unsigned char);
    case GL_UNSIGNED_INT:
      return sizeof(unsigned int);
    }
    ASSERT(false);
    return 0;
  }
};

class VertexBufferLayout {
  private:
  std::vector<VertexBufferElement> m_Elements;
  unsigned int m_stride;
public:
  VertexBufferLayout();
  
  template<typename T>
  void Push(unsigned int count);

  inline const std::vector<VertexBufferElement>& GetElements() const {return m_Elements;}
  inline unsigned int GetStride() const {return m_stride;}
};
