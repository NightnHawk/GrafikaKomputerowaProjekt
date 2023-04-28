#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, GLuint size)
{
	glGenBuffers(1, &m_ID);											// Generates an empty Vertex Buffer on GPU, and passes it's identification number to the member variable m_ID
	glBindBuffer(GL_ARRAY_BUFFER, m_ID);							// Binds the Vertex Buffer
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);		// Fills buffer with given data. OpenGL hint set to static draw. Should vertices be updated frequently, change to dynamic draw
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_ID);										// Deletes the Vertex Buffer
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_ID);							// Binds the Vertex Buffer
}

void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);								// Unbinds the Vertex Buffer; No buffer selected in the currend context afterwards
}
