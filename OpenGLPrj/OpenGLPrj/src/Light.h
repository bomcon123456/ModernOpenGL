#ifndef LIGHT_H
#define LIGHT_H
#include "Core.h"
#include <GLM/glm.hpp>

class Light
{
  public:
	Light();
	Light(float red, float green, float blue, float intensity, float diffIntensity);
	~Light();

  protected:
	glm::vec3 m_color;
	float m_ambientIntensity;
	float m_diffuseIntensity;
};

#endif