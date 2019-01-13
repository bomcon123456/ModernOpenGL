#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
uniform mat4 model;

void main()
{
	gl_Position = model * vec4(position, 1.0f);
};

#shader fragment
#version 330 core

out vec4 color;

void main()
{
	color = vec4(1.f, 0.f, 0.f, 0.f);
};