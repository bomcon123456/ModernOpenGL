#include "Light.h"

Light::Light() : m_color(glm::vec3(1.f, 1.f, 1.f)), m_ambientIntensity(1.f)
{
}

Light::Light(float red, float green, float blue, float intensity) : m_color(glm::vec3(red, green, blue)), m_ambientIntensity(intensity)
{
}

Light::~Light()
{
}

void Light::UseLight(unsigned int ambientIntensityLocation, unsigned int ambientColorLocation)
{
    glUniform3f(ambientColorLocation, m_color.x, m_color.y, m_color.z);
    glUniform1f(ambientIntensityLocation, m_ambientIntensity);
}
