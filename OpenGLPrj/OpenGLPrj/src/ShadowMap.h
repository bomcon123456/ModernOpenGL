#ifndef SHADOWMAP_H
#define SHADOWMAP_H
#include "Core.h"

class ShadowMap
{
public:
	ShadowMap();
	~ShadowMap();

	virtual bool Init(unsigned int width, unsigned int height);

	virtual void Write();
	virtual void Read(GLenum textureUnit);

	unsigned int GetShadowWidth() { return m_shawdowWidth; }
	unsigned int GetShadowHeight() { return m_shawdowHeight; }

private:
	unsigned int m_FBO, m_shadowMap;
	unsigned int m_shawdowWidth, m_shadowHeight;
};

#endif // SHADOWMAP_H
