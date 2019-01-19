#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 tex;
layout (location = 2) in vec3 normal;

uniform mat4 model;
uniform mat4 proj;
uniform mat4 view;

out vec4 vCol;
out vec2 texCoord;
out vec3 interpedNormal;

void main()
{
	gl_Position = proj * view * model * vec4(position, 1.0f);
	vCol = vec4(clamp(position,0.f,1.f), 1.f);

	texCoord = tex;
	interpedNormal = mat3(transpose(inverse(model))) * normal;
};

#shader fragment
#version 330 core

in vec4 vCol;
in vec2 texCoord;
in vec3 interpedNormal;

out vec4 color;

struct DirectionalLight
{
	vec3 color;
	float ambientIntensity;
	vec3 direction;
	float diffuseIntensity;
};

uniform sampler2D theTexture;
uniform DirectionalLight directionalLight;

void main()
{
	vec4 ambientColor = vec4(directionalLight.color, 1.f) * directionalLight.ambientIntensity;

	float diffuseFactor =  max(dot(normalize(interpedNormal), normalize(directionalLight.direction)), 0.f);
	vec4 diffuseColor = vec4(directionalLight.color, 1.f) * directionalLight.diffuseIntensity * diffuseFactor;

	color = texture(theTexture, texCoord) * (ambientColor + diffuseColor);

};