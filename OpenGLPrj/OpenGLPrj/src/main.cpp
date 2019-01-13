#include "Core.h"

#include "ShaderReader.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

void* alloca(unsigned int);

const float toRadians = 3.141559265f / 180.f;

unsigned int VAO, VBO, shader, uniformModel;
const int PositionSlot = 0;

bool direction = true;
float triOffset = 0.f;
float triMaxOffset = 0.7f;
float triIncrement = 0.00005f;

void CreateTriangle()
{
	float vertices[] = {-1.f, -1.f, 0.f, 1.f, -1.f, 0.f, 0.f, 1.f, 0.f};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

	GLCall(glVertexAttribPointer(PositionSlot, 3, GL_FLOAT, GL_FALSE, 0, 0));
	GLCall(glEnableVertexAttribArray(PositionSlot));

	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCall(glBindVertexArray(0));
}

unsigned int CompileShader(unsigned int program, GLenum shadeType, const std::string& source)
{
	unsigned int shaderSource = glCreateShader(shadeType);
	const char* src = source.c_str();

	GLCall(glShaderSource(shaderSource, 1, &src, nullptr));
	GLCall(glCompileShader(shaderSource));

	int res;
	
	glGetShaderiv(shaderSource, GL_COMPILE_STATUS, &res);
	if (res == GL_FALSE)
	{
		int length;
		glGetShaderiv(shaderSource, GL_INFO_LOG_LENGTH, &length);
		char* error = (char*)(alloca(sizeof(char) * length));
		glGetShaderInfoLog(shaderSource, length, &length, error);
		const char* st = shadeType == GL_VERTEX_SHADER ? "Vertex" : "Fragment";
		printf("[ERROR] Fail to compile %s Shader: '%s'\n", st, error);
		glDeleteShader(shaderSource);
		return 0;
	}
	return shaderSource;
}

void CreateShader()
{
	shader = glCreateProgram();

	if (!shader)
	{
		printf("[INITIALIZE] Failed to create program");
		return;
	}
	ShaderReader src = ShaderReader("res/shader/basic.shader");
	unsigned int vs = CompileShader(shader, GL_VERTEX_SHADER, src.GetVS());
	unsigned int fs = CompileShader(shader, GL_FRAGMENT_SHADER, src.GetFS());

	int res = 0;
	char eLog[1024] = {0};

	GLCall(glAttachShader(shader,vs));
	GLCall(glAttachShader(shader,fs));
	GLCall(glLinkProgram(shader));
	GLCall(glValidateProgram(shader));

	GLCall(glDeleteShader(vs));
	GLCall(glDeleteShader(fs));

	uniformModel = glGetUniformLocation(shader, "model");

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

	GLCall(glViewport(0, 0, bufferWidth, bufferHeight));
	CreateTriangle();
	CreateShader();
	do 
	{
		GLCall(glfwPollEvents());

		if (direction)
		{
			triOffset += triIncrement;
		}
		else	
		{
			triOffset -= triIncrement;
		}
		if (abs(triOffset) >= triMaxOffset)
		{
			direction = !direction;
		}
		

		GLCall(glClearColor(1.f, 1.f, 1.f, 1.f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		GLCall(glUseProgram(shader));
		
		// Create Identity Matrix
		glm::mat4 model(1.0f);
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.f, 0.f, 1.f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));

		//model = glm::translate(model, glm::vec3(triOffset, 0.f, 0.f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		GLCall(glBindVertexArray(VAO));
			GLCall(glDrawArrays(GL_TRIANGLES,0,3));
 		GLCall(glBindVertexArray(0));
		GLCall(glUseProgram(0));

		glfwSwapBuffers(myWindow);
	} while ((!glfwWindowShouldClose(myWindow)) && glfwGetKey(myWindow, GLFW_KEY_Q) != GLFW_PRESS);
	glfwTerminate();
	return 0;
}