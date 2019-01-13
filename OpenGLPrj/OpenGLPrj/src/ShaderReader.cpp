#include "ShaderReader.h"
#include <iostream>
#include <fstream>
#include <sstream>

ShaderReader::ShaderReader(const char* filePath)
{
	m_sources = ParseString(filePath);
}

ShaderReader::~ShaderReader()
{
}

ShaderReader::ShaderSource ShaderReader::ParseString(const char* filePath)
{
	std::ifstream input(filePath);
	if(!input)
	{
		std::cout << "[ERROR] Shader is not in a valid directory!" << std::endl;
		m_sources.VertexShader = m_sources.FragmentShader = "\0";
	}
	std::stringstream ss[2];
	enum class ShaderTypes
	{
		NONE = -1, VERTEX =0, FRAGMENT =1
	};
	ShaderTypes type = ShaderTypes::NONE;
	std::string line;
	while (std::getline(input, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				type = ShaderTypes::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				type = ShaderTypes::FRAGMENT;
			}
		}
		else
		{
			ss[(int)type] << line <<'\n';
		}
	}
	return { ss[0].str(), ss[1].str() };
}