#include "DirectionalLight.h"



DirectionalLight::DirectionalLight(): Light(), m_direction(glm::vec3(0.f, -1.f, 0.f))
{
}


DirectionalLight::DirectionalLight(float red, float green, float blue, float intensity, float diffIntensity, float xDir, float yDir, float zDir)
	: Light(red, green, blue, intensity, diffIntensity), m_direction(glm::vec3(xDir, yDir, zDir))
{

}

void DirectionalLight::Bind(unsigned int ambientIntensityLocation, unsigned int ambientColorLocation, unsigned int diffuseIntensityLocation, unsigned int directionLocation)
{
	GLCall(glUniform3f(ambientColorLocation, m_color.x, m_color.y, m_color.z));
	GLCall(glUniform1f(ambientIntensityLocation, m_ambientIntensity));

	GLCall(glUniform3f(directionLocation, m_direction.x, m_direction.y, m_direction.z));
	GLCall(glUniform1f(diffuseIntensityLocation, m_diffuseIntensity));
}

DirectionalLight::~DirectionalLight()
{
}
