#ifndef POINTLIGHT_H
#define POINTLIGHT_H
#include "Light.h"

class PointLight :
	public Light
{
public:
	PointLight();
	PointLight(float red, float green, float blue, float intensity, float diffIntensity,
				float xPos, float yPos, float zPos,
				float con, float lin, float exp);
	~PointLight();

	void Bind(unsigned int ambientIntensityLocation, unsigned int ambientColorLocation,
		unsigned int diffuseIntensityLocation, unsigned int positionLocation,
		unsigned int constantLocation, unsigned int linearLocation, unsigned int expLocation);

protected:
	glm::vec3 m_position;

	float m_constant, m_linear, m_exponent;
};

#endif // POINTLIGHT_H
