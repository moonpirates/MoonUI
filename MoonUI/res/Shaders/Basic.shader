#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec4 vertexColor;

out vec2 v_TexCoord;
out vec4 v_VertexColor;

uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * position;
	v_TexCoord = texCoord;
	v_VertexColor = vertexColor;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform sampler2D u_Texture;

in vec2 v_TexCoord;
in vec4 v_VertexColor;

void main()
{
	vec4 texColor = texture(u_Texture, v_TexCoord);
	//color = texColor * vec4(v_VertexColor);
	color = vec4(v_VertexColor);
};