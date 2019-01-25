#include "DirectionalLight.h"



DirectionalLight::DirectionalLight(): Light(), m_direction(glm::vec3(0.f, -1.f, 0.f))
{
}


DirectionalLight::DirectionalLight(
	unsigned int shadowWidth, unsigned int shadowHeight,
	float red, float green, float blue,
	float intensity, float diffIntensity,
	float xDir, float yDir, float zDir)
	: Light(shadowWidth, shadowHeight, red, green, blue, intensity, diffIntensity), m_direction(glm::vec3(xDir, yDir, zDir))
{
	m_lightProj = glm::ortho(-5.f, 5.f, -5.f, 5.f, 0.1f, 20.f);
}

void DirectionalLight::Bind(unsigned int ambientIntensityLocation, unsigned int ambientColorLocation, unsigned int diffuseIntensityLocation, unsigned int directionLocation)
{
	GLCall(glUniform3f(ambientColorLocation, m_color.x, m_color.y, m_color.z));
	GLCall(glUniform1f(ambientIntensityLocation, m_ambientIntensity));

	GLCall(glUniform3f(directionLocation, m_direction.x, m_direction.y, m_direction.z));
	GLCall(glUniform1f(diffuseIntensityLocation, m_diffuseIntensity));
}

glm::mat4 DirectionalLight::CalculateLightTransform()
{
	return m_lightProj * glm::lookAt(-m_direction, glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.0f, 0.f));
}

DirectionalLight::~DirectionalLight()
{
}
