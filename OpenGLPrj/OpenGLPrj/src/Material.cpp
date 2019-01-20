#include "Material.h"

Material::Material() : m_specularIntensity(0.f), m_shininess(0.f)
{
}

Material::Material(float sIntensity, float shine) : m_specularIntensity(sIntensity), m_shininess(shine)
{
}

void Material::Bind(unsigned int specularIntensityLocation, unsigned int shininessLocation)
{
    glUniform1f(specularIntensityLocation, m_specularIntensity);
    glUniform1f(shininessLocation, m_shininess);
}

Material::~Material()
{
}
