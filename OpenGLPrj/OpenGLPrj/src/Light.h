#ifndef LIGHT_H
#define LIGHT_H
#include "Core.h"
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

#include "ShadowMap.h"

class Light
{
  public:
	Light();
	Light(
		unsigned int shadowWidth, unsigned int shadowHeight,
		float red, float green, float blue,
		float intensity, float diffIntensity);
	~Light();

	ShadowMap* GetShadowMap() { return m_shadowMap; }

  protected:
	glm::vec3 m_color;
	float m_ambientIntensity;
	float m_diffuseIntensity;

	glm::mat4 m_lightProj;
	
	ShadowMap* m_shadowMap;
};

#endif