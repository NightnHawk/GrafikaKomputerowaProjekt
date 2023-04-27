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