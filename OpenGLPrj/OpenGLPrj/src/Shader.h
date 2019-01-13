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

	void Bind();
	void Unbind();


  private:
	unsigned int m_shaderID;
	unsigned int m_uniformProj;
	unsigned int m_uniformModel;
	unsigned int m_uniformView;
	ShaderReader m_source;

	unsigned int CompileShader(GLenum shaderType);
	void CreateShader();
};

#endif