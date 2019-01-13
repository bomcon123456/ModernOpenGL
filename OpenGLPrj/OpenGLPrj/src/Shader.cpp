#include "Shader.h"
void* alloca(unsigned int);

Shader::Shader(const char* filePath)
{
	m_source = ShaderReader(filePath);
    if(m_source.GetVS() != "\0" && m_source.GetFS() != "\0")
	    CreateShader();
}

Shader::~Shader()
{
	glDeleteProgram(m_shaderID);
}

unsigned int Shader::GetProjectionLocation()
{

	return m_uniformProj;
}

unsigned int Shader::GetModelLocation()
{
	return m_uniformModel;
}

unsigned int Shader::GetViewLocation()
{
	return m_uniformView;
}

void Shader::Bind()
{
	glUseProgram(m_shaderID);
}

void Shader::Unbind()
{
	glUseProgram(0);
}

unsigned int Shader::CompileShader(GLenum shaderType)
{
	unsigned int shader = glCreateShader(shaderType);
	if (!shader)
	{
		std::cout << "[INITIALIZE] Can't create shader" << std::endl;
		return 0;
	}
	std::string str;
	if (shaderType == GL_VERTEX_SHADER)
	{
		str = m_source.GetVS();
	}
	else
	{
		str = m_source.GetFS();
	}
	const char* source = str.c_str();
	glShaderSource(shader, 1, &source, nullptr);
	glCompileShader(shader);

	int res;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &res);
	if (!res)
	{
		int length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		char* error = (char*)(alloca(sizeof(char)*length));
		glGetShaderInfoLog(shader, length, &length, error);
		const char* shadeType = ((shaderType == GL_VERTEX_SHADER) ? "Vertex Shader" : "Fragment Shader");
		std::cout << "[ERROR] Compile " << shadeType << "failed: " << std::endl << error << std::endl;
		glDeleteShader(shader);
		return 0;
	}

	return shader;
}

void Shader::CreateShader()
{
	m_shaderID = glCreateProgram();
	if (!m_shaderID)
	{
		std::cout << "[INITIALIZE] Can't create program" << std::endl;
		return;
	}
	unsigned int vs = CompileShader(GL_VERTEX_SHADER);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER);
	if (vs == 0 || fs == 0)
	{
		return;
	}

	glAttachShader(m_shaderID, vs);
	glAttachShader(m_shaderID, fs);
	glLinkProgram(m_shaderID);
	glValidateProgram(m_shaderID);

	glDeleteShader(vs);
	glDeleteShader(fs);

	m_uniformModel = glGetUniformLocation(m_shaderID, "model");
	m_uniformProj = glGetUniformLocation(m_shaderID, "proj");
	m_uniformView = glGetUniformLocation(m_shaderID, "view");
}
