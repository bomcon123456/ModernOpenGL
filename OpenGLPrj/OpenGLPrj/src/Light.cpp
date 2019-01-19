#include "Light.h"

Light::Light() : m_color(glm::vec3(1.f, 1.f, 1.f)), m_ambientIntensity(1.f), m_direction(glm::vec3(0.f, -1.f, 0.f)), m_diffuseIntensity(0.f)
{
}

Light::Light(float red, float green, float blue, float intensity,
            float xDir, float yDir, float zDir, float diffIntensity) : 
            m_color(glm::vec3(red, green, blue)), m_ambientIntensity(intensity),
            m_direction(glm::vec3(xDir, yDir, zDir)), m_diffuseIntensity(diffIntensity)
{
}

Light::~Light()
{
}

void Light::UseLight(unsigned int ambientIntensityLocation, unsigned int ambientColorLocation,
                    unsigned int diffuseIntensityLocation, unsigned int directionLocation)
{
    glUniform3f(ambientColorLocation, m_color.x, m_color.y, m_color.z);
    glUniform1f(ambientIntensityLocation, m_ambientIntensity);

    glUniform3f(directionLocation, m_direction.x, m_direction.y, m_direction.z);
    glUniform1f(diffuseIntensityLocation, m_diffuseIntensity); 
}
