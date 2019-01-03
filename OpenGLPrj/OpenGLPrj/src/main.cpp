#include "Core.h"

#include "ShaderReader.h"
#include <iostream>
int main()
{
	if (glfwInit() != GLFW_TRUE)
	{
		printf("GLFW failed to init!\n");
		glfwTerminate();
		return 1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* myWindow = glfwCreateWindow(800, 600, "OpenGL Project", NULL, NULL);
	if (!myWindow)
	{
		printf("Failed to create window!\n");
		glfwTerminate();
		return 1;
	}

	int bufferWidth, bufferHeight;
	glfwGetFramebufferSize(myWindow, &bufferWidth, &bufferHeight);

	glfwMakeContextCurrent(myWindow);

	if (glewInit() != GLEW_OK)
	{
		printf("GLEW failed to init");
		glfwDestroyWindow(myWindow);
		glfwTerminate();
		return 1;
	}

	glViewport(0, 0, bufferWidth, bufferHeight);

	ShaderReader s("res/shader/basic.shader");
	std::cout << s.GetVS() << std::endl;
	std::cout << s.GetFS() << std::endl;

	while (!glfwWindowShouldClose(myWindow))
	{
		glfwPollEvents();

		glClearColor(1.f, 1.f, 1.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(myWindow);
	}
}