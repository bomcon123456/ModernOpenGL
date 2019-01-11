#include "Core.h"

#include "ShaderReader.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"

unsigned int VAO, VBO, shader;
const int PositionSlot = 0;

void CreateTriangle()
{
	  float vertices[] = {
	  	-1.f, -1.f, 0.f,
	  	 1.f, -1.f, 0.f,
	  	 0.f,  1.f, 0.f
	  };

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

int main()
{
	if (glfwInit() != GLFW_TRUE)
	{
		printf("[INITIALIZE] Failed to init GLFW");
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* myWindow = glfwCreateWindow(800, 600, "OpenGL Window", NULL, NULL);
	if (!myWindow)
	{
		printf("[INITIALIZE] Failed to create window");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(myWindow);

	int bufferWidth, bufferHeight;
	glfwGetFramebufferSize(myWindow, &bufferWidth, &bufferHeight);

	if (glewInit() != GLEW_OK)
	{
		printf("[INITIALIZE] Failed to init GLEW");
		glfwDestroyWindow(myWindow);
		glfwTerminate();
		return -1;
	}

	glewExperimental = true;

	glViewport(0, 0, bufferWidth, bufferHeight);

	while (!glfwWindowShouldClose(myWindow))
	{
		glfwPollEvents();

		glClearColor(1.f, 1.f, 1.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(myWindow);
	}

	glfwTerminate();
	return 0;
}