#define STB_IMAGE_IMPLEMENTATION

#include "Core.h"

#include "Window.h"
#include "Shader.h"
#include "Mesh.h"
#include "Camera.h"
#include "Texture.h"
#include "Light.h"
#include "Material.h"

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

Material shinyMaterial;
Material dullMaterial;

Light mainLight;

float deltaTime = 0.f;
float lastTime = 0.f;


// Vertices count = # elements of ALL vertices
// Vertices Length = # elements of a vertex
void calcAverageNormals(unsigned int* indices, unsigned int indicesCount, float* vertices,
 						unsigned int verticesCount, unsigned int verticesLength, unsigned int normalOffset)
{
	for(size_t i = 0; i < indicesCount; i+=3)
	{
		// in0, in1, in2 is currently is the x-value of position of 3 vertices of a tris.
		unsigned int in0 = indices[i] * verticesLength;
		unsigned int in1 = indices[i+1] * verticesLength;
		unsigned int in2 = indices[i+2] * verticesLength;

		// Find normal that orthogonal to that tris face.
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::normalize(glm::cross(v1, v2));

		// in0, in1 ,in2 is currently is the x-value of normal of 3 vertices of that tris.
		in0 += normalOffset;
		in1 += normalOffset;
		in2 += normalOffset;
		

		// set that normal.
		vertices[in0] += normal.x;
		vertices[in0 + 1] += normal.y;
		vertices[in0 + 2] += normal.z;

		vertices[in1] += normal.x;
		vertices[in1 + 1] += normal.y;
		vertices[in1 + 2] += normal.z;

		vertices[in2] += normal.x;
		vertices[in2 + 1] += normal.y;
		vertices[in2 + 2] += normal.z;
	}

	// Normalize those normal
	for(size_t i = 0;i < verticesCount/ verticesLength; i++)
	{
		unsigned int nOffset = i * verticesLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset +2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x;
		vertices[nOffset + 1] = vec.y;
		vertices[nOffset + 2] = vec.z;
	}
}


void CreateMeshes()
{
	float vertices[] = {
		-1.f, -1.f, -0.6f, 	0.f,  0.f,		0.f, 0.f, 0.f,
		 0.f, -1.f, 1.f, 	0.5f, 0.f,		0.f, 0.f, 0.f,
		 1.f, -1.f, -0.6f, 	1.f,  0.f,		0.f, 0.f, 0.f,
		 0.f,  1.f, 0.f, 	0.5f, 1.f,		0.f, 0.f, 0.f 
	};

	unsigned int indices[] ={
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	calcAverageNormals(indices, 12, vertices, 32, 8, 5);

	Mesh *mesh1 = new Mesh();
	mesh1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(mesh1);

	Mesh *mesh2 = new Mesh();
	mesh2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(mesh2);
}

void CreateShader()
{
	Shader *shader1 = new Shader("res/shader/basic.glsl");
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

	shinyMaterial = Material(1.f, 32);
	dullMaterial = Material(0.3f, 4);

	mainLight = Light(1.f, 1.f, 1.f, 0.1f, 2.0f, -1.f, -2.f, 0.1f);


	// Uniform Location
	unsigned int uniformModel = 0, uniformView = 0, uniformProj = 0, uniformEyePosition = 0;

	unsigned int uniformAmbientColor = 0, uniformAmbientIntensity = 0;
	unsigned int uniformDirection = 0, uniformDiffuseIntensity = 0;

	unsigned int uniformSpecularIntensity = 0, uniformShininess = 0;
	// Uniform Location


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

		GLCall(glClearColor(0.f, 0.f, 0.f, 1.f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		shaderList[0]->Bind();

			// GET UNIFORM
			uniformModel = shaderList[0]->GetModelLocation();
			uniformProj = shaderList[0]->GetProjectionLocation();
			uniformView = shaderList[0]->GetViewLocation();
			uniformEyePosition = shaderList[0]->GetEyePositionLocation();

			uniformAmbientColor = shaderList[0]->GetAmbientColorLocation();
			uniformAmbientIntensity = shaderList[0]->GetAmbientIntensityLocation();
			
			uniformDirection = shaderList[0]->GetDiffuseDirectionLocation();
			uniformDiffuseIntensity = shaderList[0]->GetDiffuseIntensityLocation();

			uniformSpecularIntensity = shaderList[0]->GetSpecularIntensityLocation();
			uniformShininess= shaderList[0]->GetShininessLocation();
			///////////////////////////

			// PROJECTION + VIEW MATRIX + Eye Position
			glm::vec3 eyePos = camera.GetCameraPosition();
			GLCall(glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.CalculateViewMatrix())));
			GLCall(glUniformMatrix4fv(uniformProj, 1, GL_FALSE, glm::value_ptr(proj)));
			GLCall(glUniform3f(uniformEyePosition, eyePos.x, eyePos.y, eyePos.z));
			////////////////////////////

			// LIGHTING
			mainLight.UseLight(uniformAmbientIntensity, uniformAmbientColor, uniformDiffuseIntensity, uniformDirection);
			///////////////////////////

			// AFFINE TRANSFORMATION
			// Create Identity Matrix
			glm::mat4 model(1.0f);
			model = glm::translate(model, glm::vec3(0.f, 0.f, -2.5f));
			model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));

			GLCall(glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model)));

			///////////////////////////



			// TEXTURE + MATERIAL + DRAW
			brickTexture.Bind();
			shinyMaterial.Bind(uniformSpecularIntensity, uniformShininess);
			///////////////////////////
			meshList[0]->RenderMesh();
			brickTexture.Unbind();
			///////////////////////////


			// Second mesh

			// MODEL MATRIX
			model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(0.f, 1.f, -2.5f));
			model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));

			GLCall(glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model)));
			//////////////////////////

			// TEXTURE + MATERIAL + DRAW
			dirtTexture.Bind();
			dullMaterial.Bind(uniformSpecularIntensity, uniformShininess);
			meshList[1]->RenderMesh();
			dirtTexture.Bind();
			/////////////////////////

		shaderList[0]->Unbind();

		window.SwapBuffers();
	};

	return 0;
}