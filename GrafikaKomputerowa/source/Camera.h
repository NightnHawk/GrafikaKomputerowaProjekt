#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "Shader.h"

class Camera
{
private:
	glm::vec3 m_Position;										// Stores the position of the Camera object within the Euclidean (XYZ) space
	glm::vec3 m_Orientation = glm::vec3(0.0f, 0.0f, -1.0f);		// Stores the orientation of the Camera object - a direction, so a normal vector the Camera suface space (screen) is facing
	glm::vec3 m_Up = glm::vec3(0.0f, 1.0f, 0.0f);				// Stores the unit vector (a normalized vector of length equal to 1) pinpointing the up direction

	int m_Width;
	int m_Height;

	float m_Speed = 0.1f;
	float m_Sensitivity = 100.0f;

public:
	Camera(const int width, const int height, glm::vec3 position) : m_Width(width), m_Height(height), m_Position(position) {};

	inline void SetSpeed(const float speed) { m_Speed = speed; }
	inline void SetSensitivity(const float sensitivity) { m_Sensitivity = sensitivity; }
	void Matrix(float FOVdegree, float nearPlane, float farPlane, Shader& shader, const std::string& uniform);
	void Inputs(GLFWwindow* window);
};