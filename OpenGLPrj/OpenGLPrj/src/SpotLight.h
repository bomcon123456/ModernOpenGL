#pragma once
#include "PointLight.h"
class SpotLight :
	public PointLight
{
public:
	SpotLight();
	SpotLight(float red, float green, float blue, float intensity, float diffIntensity,
		float xPos, float yPos, float zPos,
		float xDir, float yDir, float zDir,
		float con, float lin, float exp,
		float edge);
	~SpotLight();

	void Bind(unsigned int ambientIntensityLocation, unsigned int ambientColorLocation,
		unsigned int diffuseIntensityLocation, unsigned int positionLocation, unsigned int directionLocation,
		unsigned int constantLocation, unsigned int linearLocation, unsigned int expLocation,
		unsigned int edgeLocation);

	void SetFlash(glm::vec3 pos, glm::vec3 dir); 
private:
	glm::vec3 m_direction;

	float m_edge;
	float m_procEdge;
};

