#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Renderer.h"
#include "Texture.h"
#include "Camera.h"

void GLAPIENTRY
MessageCallback(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam)
{
	fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
		(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
		type, severity, message);
}

const static int width = 960;
const static int height = 540;

int main()
{
	if (!glfwInit())
	{
		std::cout << "GLFW::ERROR::INIT" << std::endl;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "Project", NULL, NULL);
	if (!window)
	{
		std::cout << "GLFW::ERROR::WINDOW" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	if (!gladLoadGL())
	{
		std::cout << "GLAD::ERROR::LOAD" << std::endl;
	}
	else
		std::cout << glGetString(GL_VERSION) << std::endl;

	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);

	glViewport(0, 0, width, width);

	GLfloat vertices[] =
	{
		-0.5f, -0.5f,  0.0f,  0.0f, 0.0f,	//0
		 0.5f, -0.5f,  0.0f,  1.0f, 0.0f,	//1
		 0.5f,  0.5f,  0.0f,  1.0f, 1.0f,	//2
		-0.5f,  0.5f,  0.0f,  0.0f, 1.0f	//3
	};

	GLuint indices[] =
	{
		0, 1, 2,
		0, 2, 3
	};

	VertexArray VAO;												// Generates and binds a Vertex Array Object
	VertexBuffer VBO(vertices, sizeof(vertices));					// Generates, binds and initializes a Vertex Buffer with data given
	VertexBufferLayout layout;										// Generates a layout object that stores the Vertex Buffer layout. Describes the way the GPU is to read the vertices data
	layout.Push<float>(3);
	layout.Push<float>(2);											// Adds a grouped data to layout onto the auto_incremented slot, here nr zero
	VAO.AddBuffer(VBO, layout);										// The internal function glVertexAttribPointer() binds together Vertex Array and Vertex Buffer, defining the way the buffer stream is read by GPU
	IndexBuffer EBO(indices, sizeof(indices) / sizeof(GLuint));		// Generates, binds and initializes an Index Array Object with data given. EBO is not binded to VAO in any way, thus it must be binded befr draw call to be used

	Shader shader("./resources/shaders/Basic.shader");
	shader.Bind();
	
	shader.SetUniform4f("u_Color", glm::vec4(0.0f, 0.2f, 1.0f, 1.0f));

	Texture texture("./resources/textures/brick.png");
	texture.Bind();							// Binded to 0
	shader.SetUniform1i("u_Texture", 0);	// So 0 also here

	shader.Unbind();
	VAO.Unbind();
	VBO.Unbind();
	EBO.Unbind();

	Renderer renderer;
	renderer.SetBackgroundColor(glm::vec3(0.07f, 0.13f, 0.17f));
	renderer.EnableBlend();
	renderer.EnableDepthTesting();

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	float r = 0.0f;
	float increment = 0.05f;

	while (!glfwWindowShouldClose(window))
	{
		shader.Bind();
		shader.SetUniform4f("u_Color", glm::vec4(r, 0.0f, 1.0f, 1.0f));

		camera.Matrix(45.0f, 0.1f, 100.0f, shader, "u_CamMatrix");
		camera.Inputs(window);
		renderer.Clear();
		renderer.Draw(VAO, EBO, shader);

		if (r > 1.0f)
			increment = -0.025f;
		else if (r < 0.0f)
			increment = 0.025f;
		r += increment;

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}