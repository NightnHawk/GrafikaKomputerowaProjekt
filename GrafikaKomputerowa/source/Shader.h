#pragma once

#include <string>
#include <unordered_map>
#include <glad/glad.h>
#include <glm/glm.hpp>

struct ShaderProgramSource {
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
private:
	std::string m_FilePath;
	GLuint m_ID;
	std::unordered_map<std::string, GLint> m_UniformLocationCache;

public:
	Shader(const std::string& filepath);
	~Shader();

	//Set uniforms
	void SetUniform1i(const std::string& name, GLint value);

	void SetUniform1f(const std::string& name, GLfloat value);
	void SetUniform2f(const std::string& name, glm::vec2 values);
	void SetUniform3f(const std::string& name, glm::vec3 values);
	void SetUniform4f(const std::string& name, glm::vec4 values);

	void SetUniformMat4f(const std::string& name, glm::mat4 matrix);

	void Bind() const;
	void Unbind() const;

private:
	ShaderProgramSource ParseShader(const std::string& filepath);
	GLuint CompileShader(GLuint type, const std::string& source);
	GLuint CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	GLuint getUniformLocation(const std::string& name);
};

// Shader class abstracts the handling of shaders - user-defined programs
// designed to run on some stag of a graphics processor. This class is basically
// API to simplify the usage of given shaders in OpenGL code.