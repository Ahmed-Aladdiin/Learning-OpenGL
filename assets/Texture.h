#pragma once
#include <iostream>

class Texture
{
private:
  unsigned int m_RendererID;
  std::string m_filePath;
  unsigned char* m_localBuffer;
  int m_width, m_height, m_bpp;
public:
  Texture(const std::string& filePath);
  ~Texture();

  void Bind(unsigned int slot = 0) const;
  void UnBind() const;

  inline int GetWidth() const {return m_width;}
  inline int GetHeight() const {return m_height;}
};
