#ifndef SHADER_H
#define SHADER_H

#include "Core.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "ShaderReader.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"

class Shader
{
  public:
	Shader(const char* filePath);
	~Shader();

	unsigned int GetProjectionLocation();
	unsigned int GetModelLocation();
	unsigned int GetViewLocation();
	unsigned int GetEyePositionLocation();

	unsigned int GetAmbientIntensityLocation();
	unsigned int GetAmbientColorLocation();
	unsigned int GetDiffuseIntensityLocation();
	unsigned int GetDiffuseDirectionLocation();

	unsigned int GetSpecularIntensityLocation();
	unsigned int GetShininessLocation();

	void SetDirectionalLight(DirectionalLight* dLight);
	void SetPointLights(PointLight* pLights, unsigned int lightCount);
	void SetSpotLights(SpotLight* sLights, unsigned int lightCount);

	void SetTexture(unsigned int textureUnit);
	void SetDirectionalShadowMap(unsigned int textureUnit);
	void SetDirectionalLightTransform(glm::mat4* lTransform);

	void Bind();
	void Unbind();


  private:
	unsigned int m_shaderID;

	unsigned int m_uniformProj;
	unsigned int m_uniformModel;
	unsigned int m_uniformView;
	unsigned int m_uniformEyePosition;

	unsigned int m_uniformDirectionalLightTransform;
	unsigned int m_uniformDirectionalShadowMap;
	unsigned int m_uniformTexture;

	struct {
		unsigned int uniformColor;
		unsigned int uniformAmbientIntensity;
		unsigned int uniformDiffuseIntensity;

		unsigned int uniformDirection;
	} m_uniformDirectionalLight;

	struct {
		unsigned int uniformColor;
		unsigned int uniformAmbientIntensity;
		unsigned int uniformDiffuseIntensity;

		unsigned int uniformPosition;
		unsigned int uniformConstant;
		unsigned int uniformLinear;
		unsigned int uniformExponent;
	} m_uniformPointLight[MAX_POINT_LIGHTS];

	struct {
		unsigned int uniformColor;
		unsigned int uniformAmbientIntensity;
		unsigned int uniformDiffuseIntensity;

		unsigned int uniformPosition;
		unsigned int uniformDirection;

		unsigned int uniformConstant;
		unsigned int uniformLinear;
		unsigned int uniformExponent;

		unsigned int uniformEdge;
	} m_uniformSpotLight[MAX_SPOT_LIGHTS];

	unsigned int m_uniformSpecularIntensity;
	unsigned int m_uniformShininess;
	
	unsigned int m_pointLightCount;
	unsigned int m_uniformPointLightCount;

	unsigned int m_spotLightCount;
	unsigned int m_uniformSpotLightCount;


	ShaderReader m_source;

	unsigned int CompileShader(GLenum shaderType);
	void CreateShader();
};

#endif