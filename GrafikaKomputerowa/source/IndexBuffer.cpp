#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const GLuint* data, GLuint count)
	: m_Count(count)
{
	glGenBuffers(1, &m_ID);																	// Generates a buffer on GPU and returnes its id to the member variable
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);											// Bindes the Index Buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);	// Initializes the Index Buffer. OpenGL hint set to static draw. Should vertices be updated frequently, change to dynamic draw
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_ID);						// Deletes the Index Buffer
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);	// Bindes the Index Buffer
}

void IndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);		// Unbindes the Index Buffer; No Index Buffer will result in any draw call using glDrawElements uneffecitve
}