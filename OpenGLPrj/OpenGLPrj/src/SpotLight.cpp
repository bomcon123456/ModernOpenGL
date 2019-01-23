#include "SpotLight.h"

SpotLight::SpotLight(): PointLight(), m_direction(glm::vec3(0.f, -1.f, 0.f)), m_edge(0.f), m_procEdge(cosf(glm::radians(m_edge)))
{

}

SpotLight::SpotLight(float red, float green, float blue, float intensity, float diffIntensity,
	float xPos, float yPos, float zPos,
	float xDir, float yDir, float zDir,
	float con, float lin, float exp,
	float edge)
	: PointLight(red, green, blue, intensity, diffIntensity, xPos, yPos, zPos, con, lin, exp), m_direction(glm::normalize(glm::vec3(xDir, yDir, zDir))),
	m_edge(edge), m_procEdge(cosf(glm::radians(m_edge)))
{

}

SpotLight::~SpotLight()
{

}

void SpotLight::Bind(unsigned int ambientIntensityLocation, unsigned int ambientColorLocation,
	unsigned int diffuseIntensityLocation, unsigned int positionLocation, unsigned int directionLocation,
	unsigned int constantLocation, unsigned int linearLocation, unsigned int expLocation, unsigned int edgeLocation)
{
	GLCall(glUniform3f(ambientColorLocation, m_color.x, m_color.y, m_color.z));
	GLCall(glUniform1f(ambientIntensityLocation, m_ambientIntensity));
	GLCall(glUniform1f(diffuseIntensityLocation, m_diffuseIntensity));

	GLCall(glUniform3f(positionLocation, m_position.x, m_position.y, m_position.z));
	GLCall(glUniform3f(directionLocation, m_direction.x, m_direction.y, m_direction.z));
	
	GLCall(glUniform1f(constantLocation, m_constant));
	GLCall(glUniform1f(linearLocation, m_linear));
	GLCall(glUniform1f(expLocation, m_exponent));
	GLCall(glUniform1f(edgeLocation, m_procEdge));

}

void SpotLight::SetFlash(glm::vec3 pos, glm::vec3 dir)
{
	m_position = pos;
	m_direction = dir;
}
