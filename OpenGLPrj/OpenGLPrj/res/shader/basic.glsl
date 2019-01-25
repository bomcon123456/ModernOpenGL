#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 tex;
layout (location = 2) in vec3 normal;

uniform mat4 model;
uniform mat4 proj;
uniform mat4 view;
uniform mat4 directionalLightSpaceTransform;

out vec4 vCol;
out vec2 texCoord;
out vec3 interpedNormal;
out vec3 fragPos;
out vec4 directionalLightSpacePosition;

void main()
{
	gl_Position = proj * view * model * vec4(position, 1.0f);
	directionalLightSpacePosition = directionalLightSpaceTransform * model * vec4(position, 1.0f);
	
	
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
in vec4 directionalLightSpacePosition;

out vec4 color;

const int MAX_POINT_LIGHTS = 3;
const int MAX_SPOT_LIGHTS = 3;

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

struct SpotLight
{
	PointLight base;
	vec3 direction;
	float edge;
};

struct Material
{
	float specularIntensity;
	float shininess;
};

uniform vec3 eyePosition;

// LIGHTS
uniform int pointLightCount;
uniform int spotLightCount;

uniform DirectionalLight directionalLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];
//////////////////////////

// MATERIAL + TEXTURE
uniform sampler2D theTexture;
uniform sampler2D directionalShadowMap;

uniform Material material;
//////////////////////////

float CalculateDirectionalShadowFactor(DirectionalLight light)
{
	vec3 projCoords = directionalLightSpacePosition.xyz / directionalLightSpacePosition.w;
	projCoords = (projCoords * 0.5f) + 0.5f;
	
	// Closest visible point we can see from the directional light camera
	float closest = texture(directionalShadowMap, projCoords.xy).r;
	// How far (actual depth) is that point?
	float current = projCoords.z;

	float shadow = current > closest ? 1.f : 0.f;

	return shadow;
}

vec4 CalculateLightByDirection(Light light, vec3 direction, float shadowFactor)
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

	return (ambientColor + (1.0f - shadowFactor) * (diffuseColor + specularColor));
}

vec4 CalculateDirectionalLight()
{
	float shadowFactor = CalculateDirectionalShadowFactor(directionalLight);

	return CalculateLightByDirection(directionalLight.base, directionalLight.direction, shadowFactor);
}

vec4 CalculatePointLight(PointLight pLight)
{
	vec3 direction = fragPos - pLight.position;
	float distance = length(direction);
	direction = normalize(direction);

	vec4 color = CalculateLightByDirection(pLight.base, direction, 0.f);
	float attenuation = pLight.exponent * distance * distance + pLight.linear * distance + pLight.constant;

	return (color / attenuation);
}

vec4 CalculatePointLights()
{
	vec4 result = vec4(0, 0, 0, 0);
	for(int i = 0; i < pointLightCount; i++)
	{
		result += CalculatePointLight(pointLights[i]);
	}
	return result;
}

vec4 CalculateSpotLight(SpotLight sLight)
{
	vec3 rayDirection = normalize(fragPos - sLight.base.position);
	float spotLightFactor = dot(rayDirection, sLight.direction);

	if(spotLightFactor > sLight.edge)
	{
		vec4 color = CalculatePointLight(sLight.base);

		return color * (1.f - (1.f - spotLightFactor) * (1.f / (1.f - sLight.edge)));
	}
	return vec4(0, 0, 0, 0);
}

vec4 CalculateSpotLights()
{
	vec4 result = vec4(0, 0, 0, 0);
	for(int i = 0; i < spotLightCount; i++)
	{
		result += CalculateSpotLight(spotLights[i]);
	}
	return result;
}

void main()
{
	vec4 finalColor = CalculateDirectionalLight();
	finalColor += CalculatePointLights();
	finalColor += CalculateSpotLights();
	color = texture(theTexture, texCoord) * finalColor;

};