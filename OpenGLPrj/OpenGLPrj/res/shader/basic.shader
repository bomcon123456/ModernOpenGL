#shader vertex
#version 330 core

layout(location = 0) in vec3 position;

uniform mat4 model;
uniform mat4 proj;
uniform mat4 view;

out vec4 vCol;

void main()
{
	gl_Position = proj * view * model * vec4(position, 1.0f);
	vCol = vec4(clamp(position,0.f,1.f), 1.f);
};

#shader fragment
#version 330 core

in vec4 vCol;

out vec4 color;

void main()
{
	color = vCol;
};