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
	ShaderReader() : sources() {};
	ShaderReader(const char* filePath);
	~ShaderReader();

	ShaderSource ParseString(const char* filePath);
	std::string GetVS() { return sources.VertexShader; }
	std::string GetFS() { return sources.FragmentShader; }
private:
	ShaderSource sources;
};

