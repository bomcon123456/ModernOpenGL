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
	unsigned int GetAmbientIntensityLocation();
	unsigned int GetAmbientColorLocation();
	unsigned int GetDiffuseIntensityLocation();
	unsigned int GetDiffuseDirectionLocation();

	void Bind();
	void Unbind();


  public:
	unsigned int m_shaderID;
	unsigned int m_uniformProj;
	unsigned int m_uniformModel;
	unsigned int m_uniformView;

	unsigned int m_uniformAmbientColor;
	unsigned int m_uniformAmbientIntensity;
	unsigned int m_uniformDiffuseIntensity;
	unsigned int m_uniformDiffuseDirection;
	

	ShaderReader m_source;

	unsigned int CompileShader(GLenum shaderType);
	void CreateShader();
};

#endif