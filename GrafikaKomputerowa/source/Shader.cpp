#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>

Shader::Shader(const std::string& filepath)
	: m_FilePath(filepath), m_ID(0)
{
	ShaderProgramSource source = ParseShader(filepath);
	m_ID = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader()
{
	glDeleteProgram(m_ID);
}

void Shader::SetUniform1f(const std::string& name, GLfloat value)
{
	glUniform1f(getUniformLocation(name), value);
}

void Shader::SetUniform2f(const std::string& name, glm::vec2 values)
{
	glUniform2f(getUniformLocation(name), values.x, values.y);
}

void Shader::SetUniform3f(const std::string& name, glm::vec3 values)
{
	glUniform3f(getUniformLocation(name), values.x, values.y, values.z);
}

void Shader::SetUniform4f(const std::string& name, glm::vec4 values)
{
	glUniform4f(getUniformLocation(name), values.x, values. y, values.z, values.w);
}

void Shader::Bind() const
{
	glUseProgram(m_ID);														// Binds the shader program
}

void Shader::Unbind() const
{
	glUseProgram(0);														// Unbounds the shader program; No program will be bound afterwards, thus the standard shader, if provided by the producer, will be used
}

ShaderProgramSource Shader::ParseShader(const std::string& filepath) {		// Parses the shader's code and devides it into two string streams that are then stored in strings of ShaderProgramStruct struct
	std::ifstream stream(filepath);

	enum class ShaderType {
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while (getline(stream, line)) {
		if (line.find("#shader") != std::string::npos) {
			if (line.find("vertex") != std::string::npos) {
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos) {
				type = ShaderType::FRAGMENT;
			}
		}
		else {
			ss[(int)type] << line << '\n';
		}
	}
	stream.close();
	return { ss[0].str(), ss[1].str() };
}

GLuint Shader::CompileShader(GLuint type, const std::string& source)
{
	GLuint id = glCreateShader(type);										// Creates an empty shader object and returns non-zero id value by which it can be referenced
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, NULL);										// Sets the source code in shader to the source code in the array of strings specified by string
	glCompileShader(id);													// Compiles the source code strings that have been stored in the shader object specified by shader

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);							// glGetShaderiv returns in params the value of a parameter for a specific shader object. The parameters associated with glGetShaderInfoLog are used to debug the errors and pass them ont the terminal output
	if (!result)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader." << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);													// Deletes the bugged shader
		return 0;
	}

	return id;
}

GLuint Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	GLuint program = glCreateProgram();										// Creates an empty program object and returns a non-zero value by which it can be referenced
	GLuint vs = CompileShader(GL_VERTEX_SHADER, vertexShader); 
	GLuint fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
	glAttachShader(program, vs);											// Shaders that are to be linked together in a program object must first be attached to that program object
	glAttachShader(program, fs);
	glLinkProgram(program);													// Links the program object specified by program. If any shader objects of type GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, GL_GEOMETRY_SHADER they will be used to create an executable that will run on programmable procesor
	glValidateProgram(program);												// Checks to see whether the executables contained in program can execute given the current OpenGL state

	glDeleteShader(vs);														// Delete the redundant shaders
	glDeleteShader(fs);

	return program;
}

GLuint Shader::getUniformLocation(const std::string& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];
	GLint location = glGetUniformLocation(m_ID, name.c_str());
	if (location == -1)
		std::cout << "WARNING::UNIFORM: '" << name << "' doesn't exist!" << std::endl;
	m_UniformLocationCache[name] = location;
	return location;
}
