#ifndef CORE_H
#define CORE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#define MAX_POINT_LIGHTS 3
#define MAX_SPOT_LIGHTS 3

void __debugbreak();
void GLClear();

bool GLLogError(const char* function, const char* file, int line);

#define ASSERT(x) if(!x) {__debugbreak();}

#define GLCall(x)	GLClear();\
					x;\
					ASSERT(GLLogError(#x,__FILE__,__LINE__));
					

#endif