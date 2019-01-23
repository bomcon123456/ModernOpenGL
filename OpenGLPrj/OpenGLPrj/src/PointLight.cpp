#include "PointLight.h"

PointLight::PointLight() : Light(), m_position(glm::vec3(0.f, 0.f, 0.f)), m_constant(1.0f), m_linear(0.f), m_exponent(0.f)
{

}

PointLight::PointLight(float red, float green, float blue, float intensity, float diffIntensity, float xPos, float yPos, float zPos, float con, float lin, float exp)
	: Light(red, green, blue, intensity, diffIntensity), m_position(glm::vec3(xPos, yPos, zPos)), m_constant(con), m_linear(lin), m_exponent(exp)
{

}

PointLight::~PointLight()
{
}


void PointLight::Bind(unsigned int ambientIntensityLocation, unsigned int ambientColorLocation, unsigned int diffuseIntensityLocation, unsigned int positionLocation, unsigned int constantLocation, unsigned int linearLocation, unsigned int expLocation)
{
	GLCall(glUniform3f(ambientColorLocation, m_color.x, m_color.y, m_color.z));
	GLCall(glUniform1f(ambientIntensityLocation, m_ambientIntensity));
	GLCall(glUniform1f(diffuseIntensityLocation, m_diffuseIntensity));
	
	GLCall(glUniform3f(positionLocation, m_position.x, m_position.y, m_position.z));
	GLCall(glUniform1f(constantLocation, m_constant));
	GLCall(glUniform1f(linearLocation, m_linear));
	GLCall(glUniform1f(expLocation, m_exponent));
}
