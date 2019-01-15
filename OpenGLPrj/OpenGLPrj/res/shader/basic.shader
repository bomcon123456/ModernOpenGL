#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 tex;

uniform mat4 model;
uniform mat4 proj;
uniform mat4 view;

out vec4 vCol;
out vec2 TexCoord;

void main()
{
	gl_Position = proj * view * model * vec4(position, 1.0f);
	vCol = vec4(clamp(position,0.f,1.f), 1.f);

	TexCoord = tex;
};

#shader fragment
#version 330 core

in vec4 vCol;
in vec2 TexCoord;

out vec4 color;

uniform sampler2D theTexture;

void main()
{
	color = texture(theTexture, TexCoord);
};