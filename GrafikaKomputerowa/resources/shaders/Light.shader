#shader vertex
#version 430 core

layout(location = 0) in vec4 position;

uniform mat4 u_Model;
uniform mat4 u_CamMatrix;

void main()
{
	gl_Position = u_CamMatrix * u_Model * position;
}

#shader fragment
#version 430 core

out vec4 FragColor;

uniform vec4 u_LightColor;

void main()
{
	FragColor = u_LightColor;
}