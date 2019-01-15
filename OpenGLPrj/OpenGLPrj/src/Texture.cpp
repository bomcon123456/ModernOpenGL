#include "Texture.h"

Texture::Texture() : m_textureID(0), m_width(0), m_height(0), m_bitDepth(0), m_fileLocation(nullptr)
{
}

Texture::Texture(const char* fileLoc) : m_textureID(0), m_width(0), m_height(0), m_bitDepth(0), m_fileLocation((char*)fileLoc)
{
}

void Texture::LoadTexture()
{
    unsigned char *texData = stbi_load(m_fileLocation, &m_width, &m_height, &m_bitDepth, 0);
    if (!texData)
    {
        std::cout << "[TEXTURE] Failed to find file at: " << m_fileLocation << std::endl;
        return;
    }

    GLCall(glGenTextures(1, &m_textureID));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_textureID));

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData));
    GLCall(glGenerateMipmap(GL_TEXTURE_2D));

    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
    stbi_image_free(texData);
}

void Texture::Bind()
{
    GLCall(glActiveTexture(GL_TEXTURE0));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_textureID));
}

void Texture::Unbind()
{
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}


Texture::~Texture()
{
    GLCall(glDeleteTextures(1, &m_textureID));
    m_textureID = 0;
    m_width = 0;
    m_height = 0;
    m_bitDepth = 0;
    m_fileLocation = nullptr;
}
