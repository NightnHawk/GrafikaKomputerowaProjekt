#shader vertex
#version 430 core

layout(location = 0) in vec3 position;

uniform mat4 u_CamMatrix;

void main() {

    mat4 Mesh;
    Mesh[0] = vec4(1.0, 0.0, 0.0, 1.0);
    Mesh[1] = vec4(0.0, 1.0, 0.0, 1.0);
    Mesh[2] = vec4(0.0, 0.0, 1.0, 1.0);
    Mesh[3] = vec4(0.0, 0.0, 0.0, 1.0);

    gl_Position = u_CamMatrix * Mesh * vec4(position, 1);

}

#shader fragment
#version 430 core

out vec4 FragColor;
uniform vec4 u_LightColor;

void main() {

    FragColor = u_LightColor;
}