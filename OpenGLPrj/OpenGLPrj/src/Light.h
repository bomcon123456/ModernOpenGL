#ifndef LIGHT_H
#define LIGHT_H
#include "Core.h"
#include <GLM/glm.hpp>

class Light
{
  public:
	Light();
	Light(float red, float green, float blue, float intensity, float xDir, float yDir, float zDir, float diffIntensity);
	~Light();

	void UseLight(unsigned int ambientIntensityLocation, unsigned int ambientColorLocation, unsigned int diffuseIntensityLocation, unsigned int directionLocation);

  private:
	glm::vec3 m_color;
	float m_ambientIntensity;

	glm::vec3 m_direction;
	float m_diffuseIntensity;
};

#endif