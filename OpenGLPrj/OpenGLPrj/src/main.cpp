#define STB_IMAGE_IMPLEMENTATION

#include "Core.h"

#include "Window.h"
#include "Shader.h"
#include "Mesh.h"
#include "Camera.h"
#include "Texture.h"
#include "Light.h"

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include <vector>

void *alloca(unsigned int);

const float toRadians = 3.141559265f / 180.f;

std::vector<Shader *> shaderList;
std::vector<Mesh *> meshList;
Camera camera;

Texture brickTexture;
Texture dirtTexture;

Light mainLight;

float deltaTime = 0.f;
float lastTime = 0.f;

void CreateMeshes()
{
	float vertices[] = {
		-1.f, -1.f, 0.f, 0.f,  0.f,
		 0.f, -1.f, 1.f, 0.5f, 0.f,
		 1.f, -1.f, 0.f, 1.f,  0.f,
		 0.f,  1.f, 0.f, 0.5f, 1.f
	};

	unsigned int indices[] ={
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	Mesh *mesh1 = new Mesh();
	mesh1->CreateMesh(vertices, indices, 20, 12);
	meshList.push_back(mesh1);

	Mesh *mesh2 = new Mesh();
	mesh2->CreateMesh(vertices, indices, 20, 12);
	meshList.push_back(mesh2);
}

void CreateShader()
{
	Shader *shader1 = new Shader("res/shader/basic.shader");
	shaderList.push_back(shader1);
}

int main()
{
	Window window(800, 600);
	if (!window.Initialize())
	{
		std::cout << "[INITIALIZE] Can't create Application Window." << std::endl;
		return -1;
	}

	CreateShader();
	CreateMeshes();

	camera = Camera(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f), -90.f, 0.f, 5.f, 0.5f);

	brickTexture = Texture("res/textures/brick.png");
	brickTexture.LoadTexture();

	dirtTexture = Texture("res/textures/dirt.png");
	dirtTexture.LoadTexture();

	mainLight = Light(1.f, 0.f, 1.f, 0.2f);

	unsigned int uniformModel = 0, uniformView = 0, uniformProj = 0, uniformAmbientColor = 0, uniformAmbientIntensity = 0;

	float bufferWidth = (float)window.GetBufferWidth();
	float bufferHeight = (float)window.GetBufferHeight();
	glm::mat4 proj(1.0f);
	proj = glm::perspective(45.0f, bufferWidth / bufferHeight, 0.1f, 100.f);

	while (!(window.GetShouldClose()))
	{
		float now = (float)glfwGetTime();
		deltaTime = now - lastTime;
		lastTime = now;

		GLCall(glfwPollEvents());

		camera.KeyControl(window.GetKey(), deltaTime);
		camera.MouseControl(window.GetXChange(), window.GetYChange());

		GLCall(glClearColor(1.f, 1.f, 1.f, 1.f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		shaderList[0]->Bind();

			// GET UNIFORM
			uniformModel = shaderList[0]->GetModelLocation();
			uniformProj = shaderList[0]->GetProjectionLocation();
			uniformView = shaderList[0]->GetViewLocation();
			uniformAmbientColor = shaderList[0]->GetAmbientColorLocation();
			uniformAmbientIntensity = shaderList[0]->GetAmbientIntensityLocation();
			///////////////////////////

			// LIGHTING
			mainLight.UseLight(uniformAmbientIntensity, uniformAmbientColor);

			// AFFINE TRANSFORMATION
			// Create Identity Matrix
			glm::mat4 model(1.0f);
			model = glm::translate(model, glm::vec3(0.f, 0.f, -2.5f));
			model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.f));

			glm::mat4 view = camera.CalculateViewMatrix();
			GLCall(glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model)));
			GLCall(glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view)));
			GLCall(glUniformMatrix4fv(uniformProj, 1, GL_FALSE, glm::value_ptr(proj)));
			///////////////////////////

			// TEXTURE + DRAW
			brickTexture.Bind();
			meshList[0]->RenderMesh();
			brickTexture.Unbind();
			///////////////////////////


			// Second mesh

			model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(0.f, 1.f, -2.5f));
			model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.f));

			GLCall(glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model)));
			dirtTexture.Bind();
			meshList[1]->RenderMesh();
			dirtTexture.Bind();

		shaderList[0]->Unbind();

		window.SwapBuffers();
	};

	return 0;
}