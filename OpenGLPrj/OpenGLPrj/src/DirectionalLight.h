#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H
#include "Light.h"

class DirectionalLight : public Light
{
public:
	DirectionalLight();
	~DirectionalLight();

	DirectionalLight(
		unsigned int shadowWidth, unsigned int shadowHeight,
		float red, float green, float blue,
		float intensity, float diffIntensity,
		float xDir, float yDir, float zDir);
	void Bind(unsigned int ambientIntensityLocation, unsigned int ambientColorLocation, unsigned int diffuseIntensityLocation, unsigned int directionLocation);

	glm::mat4 CalculateLightTransform();

private:
	glm::vec3 m_direction;
};

#endif // DIRECTIONALLIGHT_H
