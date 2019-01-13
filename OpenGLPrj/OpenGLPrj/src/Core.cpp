#include "Core.h"

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
