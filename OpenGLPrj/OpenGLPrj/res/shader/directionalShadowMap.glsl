#shader vertex
#version 330 core

layout(location = 0) in vec3 position;

uniform mat4 model;
uniform mat4 directionalLightSpaceTransform;	// projection * view

void main()
{
	gl_Position = directionalLightSpaceTransform * model * vec4(position, 1.0f);
}

#shader fragment
#version 330 core

void main()
{
}