#ifndef LIGHT_H
#define LIGHT_H
#include "Core.h"
#include <GLM/glm.hpp>

class Light
{
  public:
	Light();
	Light(float red, float green, float blue, float intensity);
	~Light();

	void UseLight(unsigned int ambientIntensityLocation, unsigned int ambientColorLocation);

  private:
	glm::vec3 m_color;
	float m_ambientIntensity;
};

#endif