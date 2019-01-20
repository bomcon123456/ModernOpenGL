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
out vec3 fragPos;

void main()
{
	gl_Position = proj * view * model * vec4(position, 1.0f);
	vCol = vec4(clamp(position,0.f,1.f), 1.f);

	texCoord = tex;
	interpedNormal = mat3(transpose(inverse(model))) * normal;

	fragPos = (model * vec4(position, 1.0f)).xyz;
};

#shader fragment
#version 330 core

in vec4 vCol;
in vec2 texCoord;
in vec3 interpedNormal;
in vec3 fragPos;

out vec4 color;

struct DirectionalLight
{
	vec3 color;
	float ambientIntensity;
	vec3 direction;
	float diffuseIntensity;
};

struct Material
{
	float specularIntensity;
	float shininess;
};

uniform vec3 eyePosition;

uniform sampler2D theTexture;

uniform DirectionalLight directionalLight;
uniform Material material;

void main()
{
	vec4 ambientColor = vec4(directionalLight.color, 1.f) * directionalLight.ambientIntensity;

	float diffuseFactor =  max(dot(normalize(interpedNormal), normalize(directionalLight.direction)), 0.f);
	vec4 diffuseColor = vec4(directionalLight.color, 1.f) * directionalLight.diffuseIntensity * diffuseFactor;

	vec4 specularColor = vec4(0.f, 0.f , 0.f, 0.f);
	if(diffuseFactor > 0.f)
	{
		vec3 fragToEye = normalize(eyePosition - fragPos);
		vec3 reflectedVector = normalize(reflect(directionalLight.direction, normalize(interpedNormal)));
	
		float specularFactor = dot(fragToEye, reflectedVector);
		if(specularFactor > 0.f)
		{
			specularFactor = pow(specularFactor, material.shininess);
			specularColor = vec4(directionalLight.color * material.specularIntensity * specularFactor, 1.f); 
		}
	}

	color = texture(theTexture, texCoord) * (ambientColor + diffuseColor + specularColor);

};