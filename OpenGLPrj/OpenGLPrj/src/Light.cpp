#include "Light.h"

Light::Light() : m_color(glm::vec3(1.f, 1.f, 1.f)), m_ambientIntensity(1.f), m_diffuseIntensity(0.f)
{
}

Light::Light(float red, float green, float blue, float intensity, float diffIntensity) 
	: m_color(glm::vec3(red, green, blue)), m_ambientIntensity(intensity), m_diffuseIntensity(diffIntensity)
{
}

Light::~Light()
{
}
