#pragma once

#include <glad/glad.h>
#include <string>

class Texture
{
private:
	GLuint m_ID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;

public:
	Texture(const std::string& filepath);
	~Texture();

	void Bind(GLuint slot = 0) const;
	void Unbind() const;

	inline unsigned int GetWidth() const { return m_Width; }
	inline unsigned int GetHeight() const { return m_Height; }
};