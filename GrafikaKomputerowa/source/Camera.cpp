#include "Camera.h"

#include <iostream>

void Camera::Matrix(float FOVdegree, float nearPlane, float farPlane, Shader& shader, const std::string& uniform)
{
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	view = glm::lookAt(m_Position, m_Position + m_Orientation, m_Up);
	projection = glm::perspective(glm::radians(45.0f), (float)(m_Width / m_Height), 0.1f, 100.0f);

	shader.SetUniformMat4f(uniform, projection * view);
}

void Camera::Inputs(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		m_Position += m_Speed * m_Orientation * glm::vec3(1.0f, 0.0f, 1.0f);
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		m_Position += m_Speed * -m_Orientation * glm::vec3(1.0f, 0.0f, 1.0f);
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		m_Position += m_Speed * (- glm::normalize(glm::cross(m_Orientation, m_Up)));
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		m_Position += m_Speed * glm::normalize(glm::cross(m_Orientation, m_Up));
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		m_Position += m_Speed * m_Up;
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		m_Position += m_Speed * (- m_Up);
	}

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, 1);
	}

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && m_Speed < 0.99f)
	{
		SetSpeed(m_Speed + 0.01f);
		std::cout << "Current speed: " << m_Speed << std::endl;
	}

	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && m_Speed > 0.1f)
	{
		SetSpeed(m_Speed - 0.01f);
		std::cout << "Current speed: " << m_Speed << std::endl;
	}

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);
	float rotX = m_Sensitivity * (float)(mouseY - (m_Height / 2)) / m_Height;
	float rotY = m_Sensitivity * (float)(mouseX - (m_Width / 2)) / m_Width;
	glm::vec3 newOrientation = glm::rotate(m_Orientation, glm::radians(-rotX), glm::normalize(glm::cross(m_Orientation, m_Up)));
	if (!((glm::angle(newOrientation, m_Up) <= glm::radians(5.0f)) || (glm::angle(newOrientation, -m_Up) <= glm::radians(5.0f)))) {
		m_Orientation = newOrientation;
	}
	m_Orientation = glm::rotate(m_Orientation, glm::radians(-rotY), m_Up);

	glfwSetCursorPos(window, (m_Width / 2), (m_Height / 2));
}
