#ifndef MATERIAL_H
#define MATERIAL_H

#include "Core.h"
class Material
{
  public:
	Material();
	Material(float sIntensity, float shine);
	~Material();

	void Bind(unsigned int specularIntensityLocation, unsigned int shininessLocation);

  private:
	float m_specularIntensity;
	float m_shininess;
};

#endif