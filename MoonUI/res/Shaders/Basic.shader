#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec4 vertexColor;
layout(location = 3) in float texIndex;

out vec2 v_TexCoord;
out vec4 v_VertexColor;
out float v_TexIndex;

uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * position;
	v_TexCoord = texCoord;
	v_VertexColor = vertexColor;
	v_TexIndex = texIndex;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform sampler2D u_Textures[32];

in vec2 v_TexCoord;
in vec4 v_VertexColor;
in float v_TexIndex;

void main()
{
	int index = int(v_TexIndex);
	color = texture(u_Textures[index], v_TexCoord) * v_VertexColor;
};