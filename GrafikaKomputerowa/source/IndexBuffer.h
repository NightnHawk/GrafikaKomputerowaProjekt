#pragma once

#include <glad/glad.h>

class IndexBuffer
{
private:
	GLuint m_ID;
	GLuint m_Count;
public:
	IndexBuffer(const GLuint* data, GLuint count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	inline GLuint GetCount() const { return m_Count; }	// Returns index count member variable
};

// IndexBuffer class abstracts the vertex specification of OpenGL.
// Index rendering, draw call glDrawElements, requires an array of
// indices. The index array is provided by a Buffer Object bound
// to the GL_ELEMENT_ARRAY_BUFFER binding point, which is generalized
// by this class.