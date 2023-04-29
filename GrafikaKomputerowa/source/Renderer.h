#pragma once

#include <glad/glad.h>

#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

class Renderer
{
private:
	glm::vec3 m_BackgroundColor;

public:
	Renderer() : m_BackgroundColor(glm::vec3(0.0f, 0.0f, 0.0f)) {};

	void EnableBlend() const;
	void EnableDepthTesting() const;
	void EnableBackfaceCulling() const;
	void SetBackgroundColor(glm::vec3 RGB) { m_BackgroundColor = RGB; }
	void Clear() const;
	void Draw(const VertexArray& VAO, const IndexBuffer& EBO, const Shader& shader) const;
};