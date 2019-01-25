#include "ShadowMap.h"



ShadowMap::ShadowMap(): m_FBO(0), m_shadowMap(0)
{
}


ShadowMap::~ShadowMap()
{
	if (m_FBO)
	{
		GLCall(glDeleteFramebuffers(1, &m_FBO));
	}
	if (m_shadowMap)
	{
		GLCall(glDeleteTextures(1, &m_shadowMap));
	}
}

bool ShadowMap::Init(unsigned int width, unsigned int height)
{
	m_shawdowWidth = width;
	m_shadowHeight = height;

	GLCall(glGenFramebuffers(1, &m_FBO));

	GLCall(glGenTextures(1, &m_shadowMap));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_shadowMap));
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, m_shawdowWidth, m_shadowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_FBO));
	GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_shadowMap, 0));

	GLCall(glDrawBuffer(GL_NONE));
	GLCall(glReadBuffer(GL_NONE));

	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "[FRAMEBUFFER] Error: " << status << std::endl;
		return false;
	}

	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));

	return true;
}

void ShadowMap::Write()
{
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_FBO));

}

void ShadowMap::Read(GLenum textureUnit)
{
	GLCall(glActiveTexture(textureUnit));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_shadowMap));
}
