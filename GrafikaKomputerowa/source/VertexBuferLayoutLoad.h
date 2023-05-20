#pragma once

#include <glad/glad.h>
#include <vector>
#include <stdexcept>
#include <glm/glm.hpp>

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

	template<>
	void Push<glm::vec3>(GLuint count) {
		m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_Stride += sizeof(GLubyte) * count;
	}

	inline const std::vector<VertexBufferElement>& GetElements() const { return m_Elements; }
	inline GLuint GetStride() const { return m_Stride; }
};

// VertexBufferLayout is an auxiliary class used to automatically
// specify the location and data format of the array of generic
// vertex attributes at given index (specified in the VertexArray
// class method) to use when rendering.
// In simplification, only vertex attributes passed into the
// VertexBufferElement vector, of the unsigned int (GLuint) type
// are normalized by GPU.