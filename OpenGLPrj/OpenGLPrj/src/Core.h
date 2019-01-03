#pragma once

#include <iostream>

#include <gl/glew.h>
#include <glfw/glfw3.h>

void GLClear()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogError(const char* function, const char* file, int line)
{
	if (GLenum err = glGetError())
	{
		std::cout << "[OPENGL Error]: Function: " << function << " in file: " << file << " at line: " << line << "." << std::endl;
		return false;
	}
	return true;
}

#define ASSERT(x) if(!x) {__debugbreak();}

#define GLCall(x)	GLClear();\
					x;\
					ASSERT(GLLogError(#x,__FILE__,__LINE__));