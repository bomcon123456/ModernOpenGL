#include "Core.h"

#include "ShaderReader.h"
#include "Window.h"
#include "Shader.h"
#include "Mesh.h"

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include <vector>


void* alloca(unsigned int);

const float toRadians = 3.141559265f / 180.f;

std::vector<Shader*> shaderList;
std::vector<Mesh*> meshList;

void CreateMeshes()
{
	float vertices[] = {
		-1.f, -1.f, 0.f,
		 0.f, -1.f, 1.f,
		 1.f, -1.f, 0.f,
		 0.f, 1.f, 0.f
	};

	unsigned int indices[] ={
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	Mesh* mesh1 = new Mesh();
	mesh1->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(mesh1);

	Mesh* mesh2 = new Mesh();
	mesh2->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(mesh2);

}

void CreateShader()
{
	Shader* shader1 = new Shader("res/shader/basic.shader");
	shaderList.push_back(shader1);
}

int main()
{
	Window window(800,600);
	if(!window.Initialize())
	{
		std::cout<< "[INITIALIZE] Can't create Application Window." << std::endl;
		return -1;
	}

	CreateShader();
	CreateMeshes();

	float bufferWidth = (float)window.GetBufferWidth();
	float bufferHeight = (float)window.GetBufferHeight();

	glm::mat4 proj(1.0f);
	glm::mat4 view(1.0f);
	unsigned int uniformModel = 0, uniformView = 0, uniformProj = 0;

	proj = glm::perspective(45.0f, bufferWidth / bufferHeight, 0.1f, 100.f);

	do 
	{
		GLCall(glfwPollEvents());

		GLCall(glClearColor(1.f, 1.f, 1.f, 1.f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		shaderList[0]->Bind();

			uniformModel = shaderList[0]->GetModelLocation();
			uniformView = shaderList[0]->GetProjectionLocation();
			uniformProj = shaderList[0]->GetViewLocation();

			// Create Identity Matrix
			glm::mat4 model(1.0f);
			model = glm::translate(model, glm::vec3(0.f, 0.f, -2.5f));
			model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.f));

			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));
			glUniformMatrix4fv(uniformProj, 1, GL_FALSE, glm::value_ptr(proj));

			meshList[0]->RenderMesh();
			
			model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(0.f, 1.f, -2.5f));
			model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.f));

			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			meshList[1]->RenderMesh();

		shaderList[0]->Unbind();

		window.SwapBuffers();
	} while ((!(window.GetShouldClose())));

	return 0;
}