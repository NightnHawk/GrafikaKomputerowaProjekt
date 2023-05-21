#shader vertex
#version 430 core

//na razie olaæ mo¿e nic nie zepsuje



layout(location = 0) in vec3 position;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 texCoord;

out vec2 v_TexCoord;
out vec3 v_aNormal;
out vec3 v_CrntPos;
out vec4 color1;



/*uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Proj;*/
uniform mat4 u_CamMatrix;


void main()
{
	
	mat3 Mesh;
	Mesh[0] = vec3(0.0, 0.0, 0.0);
	Mesh[1] = vec3(0.0, 0.0, 0.0);
	Mesh[2] = vec3(0.0, 0.0, -4.0);

	gl_Position = u_CamMatrix * vec4(position, 1);
	v_TexCoord = texCoord;
	v_aNormal = aNormal;
	v_CrntPos = vec3(Mesh * position);

    color1 = vec4(1.0, 1.0, 1.0, 1.0);
}



#shader fragment
#version 430 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in vec3 v_aNormal;
in vec3 v_CrntPos;
in vec4 color1;


// vec4 u_Color;
uniform sampler2D u_Texture;
uniform vec4 u_LightColor;
uniform vec3 u_LightPos;
uniform vec3 u_Cam;

vec4 PointLight() {
    vec3 lightVec = u_LightPos - v_CrntPos;

    float dist = length(lightVec);
    float a = 3.0;
    float b = 0.3;
    float inten = 3.0f / (a * dist * dist + b * dist + 1.0f);

    float ambient = 0.80f;


    vec3 normal = normalize(v_aNormal);
    vec3 lightDirection = normalize(lightVec);
    float diffuse = max(dot(normal, lightDirection), 0.0f);

    // specular lighting
    float specularLight = 0.50f;
    vec3 viewDirection = normalize(u_Cam - v_CrntPos);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 32);
    float specular = specAmount * specularLight;

    return u_LightColor * (color1 * (diffuse + inten + ambient));
    //return (texture(u_Texture, v_TexCoord) * (diffuse * inten + ambient));

}

void main()
{
	//vec4 texColor = texture(u_Texture, v_TexCoord);
	color = PointLight();

}