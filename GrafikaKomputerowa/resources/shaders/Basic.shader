#shader vertex
#version 430 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;

/*uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Proj;*/
uniform mat4 u_CamMatrix;

void main()
{
	gl_Position = u_CamMatrix * position;
	v_TexCoord = texCoord;
}

#shader fragment
#version 430 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main()
{
	vec4 texColor = texture(u_Texture, v_TexCoord);
	color = u_Color * texColor;
}