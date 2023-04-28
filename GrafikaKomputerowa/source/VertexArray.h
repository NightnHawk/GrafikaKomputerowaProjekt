#pragma once

#include <glad/glad.h>

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{
private:
	GLuint m_ID;
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& VertexBuffer, VertexBufferLayout& layout);

	void Bind() const;
	void Unbind() const;
};

// VertexArray class abstracts the vertex specification of OpenGL
// by automating the proces of setting the attributes (AddBuffer
// method) with connection to VertexBufferLayout object.
// For each attribute in the shader an array of data for that
// attribute must be provided. In a nutshell, set of attributes
// defines what values the vertex stream must provide to properly
// render with given shader.