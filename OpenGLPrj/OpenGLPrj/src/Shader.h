#ifndef SHADER_H
#define SHADER_H

#include "Core.h"

#include "ShaderReader.h"
class Shader
{
  public:
	Shader(const char* filePath);
	~Shader();

	unsigned int GetProjectionLocation();
	unsigned int GetModelLocation();
	unsigned int GetViewLocation();
	unsigned int GetEyePositionLocation();

	unsigned int GetAmbientIntensityLocation();
	unsigned int GetAmbientColorLocation();
	unsigned int GetDiffuseIntensityLocation();
	unsigned int GetDiffuseDirectionLocation();

	unsigned int GetSpecularIntensityLocation();
	unsigned int GetShininessLocation();

	void Bind();
	void Unbind();


  private:
	unsigned int m_shaderID;
	unsigned int m_uniformProj;
	unsigned int m_uniformModel;
	unsigned int m_uniformView;
	unsigned int m_uniformEyePosition;

	unsigned int m_uniformAmbientColor;
	unsigned int m_uniformAmbientIntensity;
	unsigned int m_uniformDiffuseIntensity;
	unsigned int m_uniformDiffuseDirection;

	unsigned int m_uniformSpecularIntensity;
	unsigned int m_uniformShininess;
	

	ShaderReader m_source;

	unsigned int CompileShader(GLenum shaderType);
	void CreateShader();
};

#endif