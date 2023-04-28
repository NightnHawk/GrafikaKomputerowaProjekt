#include "Renderer.h"

void Renderer::Clear() const
{

	glClearColor(m_BackgroundColor.x, m_BackgroundColor.y, m_BackgroundColor.z, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Draw(const VertexArray& VAO, const IndexBuffer& EBO, const Shader& shader) const
{
	shader.Bind();
	VAO.Bind();													//Binds Vertex Array Object to be used in a draw call. Given Vertex Buffer is binded along with it by glVertexAttribPointer() before so it doesn't have to be bound
	EBO.Bind();													//Binds Index Buffer Object to be used in a draw call. A specified Index Bufer has to always be bound to draw a given model.
	glDrawElements(GL_TRIANGLES, EBO.GetCount(), GL_UNSIGNED_INT, NULL);
}

void Renderer::EnableBlend() const
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


