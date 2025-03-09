#include "Texture.h"

#include <glad/glad.h>
#include <stb_image.h>

#include "Common.h"

Texture::Texture(const std::string& filePath)
: m_width(0), m_height(0), m_bpp(0), m_localBuffer(nullptr), m_RendererID(0)
{
  // when getting the stb library 
  // you need to flip the image as png is coordinate start from top left
  // while openGL reads the texture from bottom left

  // now you need to load the texture data
  stbi_set_flip_vertically_on_load(1);
  m_localBuffer = stbi_load(filePath.c_str(), &m_width, &m_height, &m_bpp, 4);

  GLCall(glGenTextures(1, &m_RendererID));
  GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));

  // you need to specify some parameters
  // min filter, max filter 
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR)); 
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)); 
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE)); 
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE)); 

  // load the data to the texture
  GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer));
  GLCall(glBindTexture(GL_TEXTURE_2D, 0));

  if(m_localBuffer)
    stbi_image_free(m_localBuffer);
}

Texture::~Texture()
{
  GLCall(glDeleteTextures(1, &m_RendererID));
}

void Texture::Bind(unsigned int slot) const
{
  GLCall(glActiveTexture(GL_TEXTURE0 + slot));
  GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void Texture::UnBind() const
{
  GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
