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

const int MAX_POINT_LIGHTS = 3;

struct Light
{
	vec3 color;
	float ambientIntensity;
	float diffuseIntensity;
};

struct DirectionalLight
{
	Light base;
	vec3 direction;
};

struct PointLight
{
	Light base;
	vec3 position;
	float constant;
	float linear;
	float exponent;
};

struct Material
{
	float specularIntensity;
	float shininess;
};

uniform vec3 eyePosition;

// LIGHTS
uniform int pointLightCount;

uniform DirectionalLight directionalLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
//////////////////////////

// MATERIAL + TEXTURE
uniform sampler2D theTexture;
uniform Material material;
//////////////////////////

vec4 CalculateLightByDirection(Light light, vec3 direction)
{
	vec4 ambientColor = vec4(light.color, 1.f) * light.ambientIntensity;

	float diffuseFactor =  max(dot(normalize(interpedNormal), normalize(direction)), 0.f);
	vec4 diffuseColor = vec4(light.color, 1.f) * light.diffuseIntensity * diffuseFactor;

	vec4 specularColor = vec4(0.f, 0.f , 0.f, 0.f);
	if(diffuseFactor > 0.f)
	{
		vec3 fragToEye = normalize(eyePosition - fragPos);
		vec3 reflectedVector = normalize(reflect(direction, normalize(interpedNormal)));
	
		float specularFactor = dot(fragToEye, reflectedVector);
		if(specularFactor > 0.f)
		{
			specularFactor = pow(specularFactor, material.shininess);
			specularColor = vec4(light.color * material.specularIntensity * specularFactor, 1.f); 
		}
	}

	return (ambientColor + diffuseColor + specularColor);
}

vec4 CalculateDirectionalLight()
{
	return CalculateLightByDirection(directionalLight.base, directionalLight.direction);
}

vec4 CalculatePointLights()
{
	vec4 result = vec4(0, 0, 0, 0);
	for(int i = 0; i < pointLightCount; i++)
	{
		vec3 direction = fragPos - pointLights[i].position;
		float distance = length(direction);
		direction = normalize(direction);

		vec4 color = CalculateLightByDirection(pointLights[i].base, direction);
		float attenuation = pointLights[i].exponent * distance * distance + pointLights[i].linear * distance + pointLights[i].constant;
		result += (color / attenuation);
	}
	return result;
}

void main()
{
	vec4 finalColor = CalculateDirectionalLight();
	finalColor += CalculatePointLights();
	color = texture(theTexture, texCoord) * finalColor;

};