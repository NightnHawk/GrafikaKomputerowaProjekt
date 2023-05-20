#shader vertex
#version 430 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 vecNormal;

out vec2 v_TexCoord;
out vec3 v_Normal;
out vec3 v_CrntPos;

/*uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Proj;*/
uniform mat4 u_CamMatrix;
uniform mat4 u_Model;

void main()
{
	v_CrntPos = vec3(u_Model * position);
	gl_Position = u_CamMatrix * position;
	v_TexCoord = texCoord;
	v_Normal = vecNormal;
}

#shader fragment
#version 430 core

layout(location = 0) out vec4 FragColor;

in vec2 v_TexCoord;
in vec3 v_Normal;
in vec3 v_CrntPos;

/*uniform vec4 u_Color;*/
uniform sampler2D u_Texture;

uniform vec4 u_LightColor;
uniform vec3 u_LightPos;
uniform vec3 u_CamPos;

vec4 pointLight()
{
	vec3 lightVec = u_LightPos - v_CrntPos;

	float dist = length(lightVec);
	float a = 3.0;
	float b = 0.7;
	float inten = 1.0f / (a * dist * dist + b * dist + 1.0f);

	float ambient = 0.20f;

	vec3 normal = normalize(v_Normal);
	vec3 lightDirection = normalize(lightVec);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// specular lighting
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(u_CamPos - v_CrntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	return (texture(u_Texture, v_TexCoord) * (diffuse * inten + ambient)); /*+texture(tex1, texCoord).r * specular * inten) * lightColor;*/
}

void main()
{
	vec4 texColor = texture(u_Texture, v_TexCoord);
	FragColor = /*u_Color * texColor;*/ pointLight();
}