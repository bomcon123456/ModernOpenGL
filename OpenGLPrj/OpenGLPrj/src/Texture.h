#ifndef TEXTURE_H
#define TEXTURE_H

#include "Core.h"
#include "stb/stb_image.h"

class Texture
{
  public:
	Texture();
	Texture(const char *fileLoc);

	bool LoadTextureNoAlpha();
	bool LoadTextureAlpha();

	void Bind();
	void Unbind();

	~Texture();

  private:
	unsigned int m_textureID;
	int m_width, m_height, m_bitDepth;

	char *m_fileLocation;
};

#endif