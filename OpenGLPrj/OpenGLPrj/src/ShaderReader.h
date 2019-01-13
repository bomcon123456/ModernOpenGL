#pragma once
#include <string>
class ShaderReader
{
public:
	struct ShaderSource 
	{
		std::string VertexShader;
		std::string FragmentShader;

		ShaderSource() :VertexShader(""), FragmentShader("") {};
		ShaderSource(std::string vs, std::string fs) :VertexShader(vs), FragmentShader(fs) {};
	};
public:
	ShaderReader() : m_sources() {};
	ShaderReader(const char* filePath);
	~ShaderReader();

	ShaderSource ParseString(const char* filePath);
	std::string GetVS() { return m_sources.VertexShader; }
	std::string GetFS() { return m_sources.FragmentShader; }
private:
	ShaderSource m_sources;
};

