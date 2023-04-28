#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_ID);							// Generates a Vertex Array on GPU and return its address to the given member variable
	glBindVertexArray(m_ID);								// Binds the Vertex Array
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_ID);							// Deletes the Vertex Array
}

void VertexArray::AddBuffer(const VertexBuffer& VertexBuffer, VertexBufferLayout& layout)
{
	this->Bind();											// To set attributes to the specified Vertex Array it must be binded, thus we bind the VertexArray edited
	VertexBuffer.Bind();									// glVertexAttribPointer(), by setting the vertex stream attributes, binds the currently binded Vertex Buffer and Vertex Array together, thus we bind the passed Vertex Buffer
	const auto& elements = layout.GetElements();
	GLuint offset = 0;
	for (GLuint i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		glEnableVertexAttribArray(i);																								// For each attribute there is a slot number assigned
		glVertexAttribPointer(i, element.s_Count, element.s_Type, element.s_Normlized, layout.GetStride(), (const void*)offset);	// Assignes the attribute at the given index i with data provided by VertexBufferLayout object
		offset += element.s_Count * sizeof(element.s_Type);																			// Calculates the offset for the following attribute
	}
}	

void VertexArray::Bind() const
{
	glBindVertexArray(m_ID);								// Bindes the Vertex Array
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);									//Unbindes the Vertex Array; No current Vertex Array  used afterwards
}
