#include "Shader.h"

void* alloca(unsigned int);

Shader::Shader(const char* filePath)
{
	m_source = ShaderReader(filePath);
    if(m_source.GetVS() != "\0" && m_source.GetFS() != "\0")
	    CreateShader();
	m_pointLightCount = 0;
	m_spotLightCount = 0;
}

Shader::~Shader()
{
	GLCall(glDeleteProgram(m_shaderID));
}

unsigned int Shader::GetProjectionLocation()
{

	return m_uniformProj;
}

unsigned int Shader::GetModelLocation()
{
	return m_uniformModel;
}

unsigned int Shader::GetViewLocation()
{
	return m_uniformView;
}

unsigned int Shader::GetEyePositionLocation()
{
	return m_uniformEyePosition;
}

unsigned int Shader::GetAmbientColorLocation()
{
	return m_uniformDirectionalLight.uniformColor;
}

unsigned int Shader::GetAmbientIntensityLocation()
{
	return m_uniformDirectionalLight.uniformAmbientIntensity;
}

unsigned int Shader::GetDiffuseIntensityLocation()
{
	return m_uniformDirectionalLight.uniformDiffuseIntensity;
}

unsigned int Shader::GetDiffuseDirectionLocation()
{
	return m_uniformDirectionalLight.uniformDirection;
}

unsigned int Shader::GetSpecularIntensityLocation()
{
	return m_uniformSpecularIntensity;

}

unsigned int Shader::GetShininessLocation()
{
	return m_uniformShininess;
}

void Shader::SetDirectionalLight(DirectionalLight* dLight)
{
	dLight->Bind(m_uniformDirectionalLight.uniformAmbientIntensity, m_uniformDirectionalLight.uniformColor, m_uniformDirectionalLight.uniformDiffuseIntensity, m_uniformDirectionalLight.uniformDirection);
}

void Shader::SetPointLights(PointLight* pLights, unsigned int lightCount)
{
	if (lightCount > MAX_POINT_LIGHTS)
	{
		lightCount = MAX_POINT_LIGHTS;
	}
	GLCall(glUniform1i(m_uniformPointLightCount, lightCount));

	for (size_t i = 0; i < lightCount; i++)
	{
		pLights[i].Bind(m_uniformPointLight[i].uniformAmbientIntensity, m_uniformPointLight[i].uniformColor, m_uniformPointLight[i].uniformDiffuseIntensity,
			m_uniformPointLight[i].uniformPosition,
			m_uniformPointLight[i].uniformConstant, m_uniformPointLight[i].uniformLinear, m_uniformPointLight[i].uniformExponent);
	}
}

void Shader::SetSpotLights(SpotLight* sLights, unsigned int lightCount)
{
	if (lightCount > MAX_SPOT_LIGHTS)
	{
		lightCount = MAX_SPOT_LIGHTS;
	}
	GLCall(glUniform1i(m_uniformSpotLightCount, lightCount));

	for (size_t i = 0; i < lightCount; i++)
	{
		sLights[i].Bind(m_uniformSpotLight[i].uniformAmbientIntensity, m_uniformSpotLight[i].uniformColor,
			m_uniformSpotLight[i].uniformDiffuseIntensity, m_uniformSpotLight[i].uniformPosition, m_uniformSpotLight[i].uniformDirection,
			m_uniformSpotLight[i].uniformConstant, m_uniformSpotLight[i].uniformLinear, m_uniformSpotLight[i].uniformExponent,
			m_uniformSpotLight[i].uniformEdge);
	}
}

void Shader::SetTexture(unsigned int textureUnit)
{
	GLCall(glUniform1f(m_uniformTexture, textureUnit));
}

void Shader::SetDirectionalShadowMap(unsigned int textureUnit)
{
	GLCall(glUniform1f(m_uniformDirectionalShadowMap, textureUnit));
}

void Shader::SetDirectionalLightTransform(glm::mat4* lTransform)
{
	GLCall(glUniformMatrix4fv(m_uniformDirectionalLightTransform, 1, GL_FALSE, glm::value_ptr(*lTransform)));
}

void Shader::Bind()
{
	GLCall(glUseProgram(m_shaderID));
}

void Shader::Unbind()
{
	GLCall(glUseProgram(0));
}

unsigned int Shader::CompileShader(GLenum shaderType)
{
	GLCall(unsigned int shader = glCreateShader(shaderType));
	if (!shader)
	{
		std::cout << "[INITIALIZE] Can't create shader" << std::endl;
		return 0;
	}
	std::string str;
	if (shaderType == GL_VERTEX_SHADER)
	{
		str = m_source.GetVS();
	}
	else
	{
		str = m_source.GetFS();
	}
	const char* source = str.c_str();
	GLCall(glShaderSource(shader, 1, &source, nullptr));
	GLCall(glCompileShader(shader));

	int res;
	GLCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &res));
	if (!res)
	{
		int length;
		GLCall(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length));
		char* error = (char*)(alloca(sizeof(char)*length));
		GLCall(glGetShaderInfoLog(shader, length, &length, error));
		const char* shadeType = ((shaderType == GL_VERTEX_SHADER) ? "Vertex Shader" : "Fragment Shader");
		std::cout << "[ERROR] Compile " << shadeType << "failed: " << std::endl << error << std::endl;
		GLCall(glDeleteShader(shader));
		return 0;
	}

	return shader;
}

void Shader::CreateShader()
{
	GLCall(m_shaderID = glCreateProgram());
	if (!m_shaderID)
	{
		std::cout << "[INITIALIZE] Can't create program" << std::endl;
		return;
	}
	unsigned int vs = CompileShader(GL_VERTEX_SHADER);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER);
	if (vs == 0 || fs == 0)
	{
		return;
	}

	GLCall(glAttachShader(m_shaderID, vs));
	GLCall(glAttachShader(m_shaderID, fs));
	GLCall(glLinkProgram(m_shaderID));
	GLCall(glValidateProgram(m_shaderID));

	GLCall(glDeleteShader(vs));
	GLCall(glDeleteShader(fs));

	GLCall(m_uniformModel = glGetUniformLocation(m_shaderID, "model"));
	GLCall(m_uniformProj = glGetUniformLocation(m_shaderID, "proj"));
	GLCall(m_uniformView = glGetUniformLocation(m_shaderID, "view"));
	GLCall(m_uniformEyePosition = glGetUniformLocation(m_shaderID, "eyePosition"));


	GLCall(m_uniformDirectionalLight.uniformColor = glGetUniformLocation(m_shaderID, "directionalLight.base.color"));
	GLCall(m_uniformDirectionalLight.uniformAmbientIntensity = glGetUniformLocation(m_shaderID, "directionalLight.base.ambientIntensity"));
	GLCall(m_uniformDirectionalLight.uniformDiffuseIntensity = glGetUniformLocation(m_shaderID, "directionalLight.base.diffuseIntensity"));
	GLCall(m_uniformDirectionalLight.uniformDirection = glGetUniformLocation(m_shaderID, "directionalLight.direction"));

	GLCall(m_uniformSpecularIntensity = glGetUniformLocation(m_shaderID, "material.specularIntensity"));
	GLCall(m_uniformShininess = glGetUniformLocation(m_shaderID, "material.shininess"));

	GLCall(m_uniformTexture = glGetUniformLocation(m_shaderID, "theTexture"));
	GLCall(m_uniformDirectionalLightTransform = glGetUniformLocation(m_shaderID, "directionalLightSpaceTransform"));
	GLCall(m_uniformDirectionalShadowMap = glGetUniformLocation(m_shaderID, "directionalShadowMap"));



	GLCall(m_uniformPointLightCount = glGetUniformLocation(m_shaderID, "pointLightCount"));

	for (size_t i = 0; i < MAX_POINT_LIGHTS; i++)
	{
		char locBuff[100] = { '\0' };
		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.color", i);
		m_uniformPointLight[i].uniformColor = glGetUniformLocation(m_shaderID, locBuff);
		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.diffuseIntensity", i);
		m_uniformPointLight[i].uniformDiffuseIntensity= glGetUniformLocation(m_shaderID, locBuff);
		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.ambientIntensity", i);
		m_uniformPointLight[i].uniformAmbientIntensity = glGetUniformLocation(m_shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].position", i);
		m_uniformPointLight[i].uniformPosition= glGetUniformLocation(m_shaderID, locBuff);
		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].constant", i);
		m_uniformPointLight[i].uniformConstant = glGetUniformLocation(m_shaderID, locBuff);
		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].linear", i);
		m_uniformPointLight[i].uniformLinear = glGetUniformLocation(m_shaderID, locBuff);
		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].exponent", i);
		m_uniformPointLight[i].uniformExponent = glGetUniformLocation(m_shaderID, locBuff);
	}

	GLCall(m_uniformSpotLightCount = glGetUniformLocation(m_shaderID, "spotLightCount"));

	for (size_t i = 0; i < MAX_SPOT_LIGHTS; i++)
	{
		char locBuff[100] = { '\0' };
		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.base.color", i);
		m_uniformSpotLight[i].uniformColor = glGetUniformLocation(m_shaderID, locBuff);
		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.base.diffuseIntensity", i);
		m_uniformSpotLight[i].uniformDiffuseIntensity= glGetUniformLocation(m_shaderID, locBuff);
		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.base.ambientIntensity", i);
		m_uniformSpotLight[i].uniformAmbientIntensity = glGetUniformLocation(m_shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.position", i);
		m_uniformSpotLight[i].uniformPosition= glGetUniformLocation(m_shaderID, locBuff);
		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.constant", i);
		m_uniformSpotLight[i].uniformConstant = glGetUniformLocation(m_shaderID, locBuff);
		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.linear", i);
		m_uniformSpotLight[i].uniformLinear = glGetUniformLocation(m_shaderID, locBuff);
		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.exponent", i);
		m_uniformSpotLight[i].uniformExponent = glGetUniformLocation(m_shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].direction", i);
		m_uniformSpotLight[i].uniformDirection = glGetUniformLocation(m_shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].edge", i);
		m_uniformSpotLight[i].uniformEdge = glGetUniformLocation(m_shaderID, locBuff);
	}
	
}
