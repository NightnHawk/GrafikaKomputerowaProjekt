#shader vertex
#version 430 core

layout(location = 0) in vec3 position;

uniform mat4 u_CamMatrix;
uniform vec3 u_Pos;

void main() {

    gl_Position = u_CamMatrix * vec4(position+u_Pos, 1);

}

#shader fragment
#version 430 core

out vec4 FragColor;
uniform vec4 u_LightColor;

void main() {

    FragColor = u_LightColor;
}