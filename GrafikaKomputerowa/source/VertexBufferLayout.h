#pragma once

#include <glad/glad.h>
#include <vector>
#include <stdexcept>

struct VertexBufferElement
{
	GLuint s_Type;
	GLuint s_Count;
	GLubyte s_Normlized;
};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> m_Elements;
	GLuint m_Stride;

public:
	VertexBufferLayout() : m_Stride(0) {};

	template<typename T>
	void Push(GLuint count)
	{
		std::runtime_error(false);
	}

	template<>
	void Push<float>(GLuint count)
	{
		m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
		m_Stride += sizeof(GLfloat) * count;
	}

	template<>
	void Push<unsigned int>(GLuint count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_Stride += sizeof(GLuint) * count;
	}

	template<>
	void Push<unsigned char>(GLuint count)
	{
		m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_Stride += sizeof(GLubyte) * count;
	}

	inline const std::vector<VertexBufferElement>& GetElements() const { return m_Elements; }
	inline GLuint GetStride() const { return m_Stride; }
};