#pragma once

#include <glad/glad.h>

class VertexBuffer
{
private:
	GLuint m_ID;
public:
	VertexBuffer(const void* data, GLuint size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
};

// VertexBuffer class abstracts the vertex specification
// of OpenGL by taking care of binding or passing the data
// to vertex stream. Complemented by VertexBufferLayout it
// stores the complete stream of vertices used to render
// primitives by using current shader program (Vertex
// shader) or program pipeline.