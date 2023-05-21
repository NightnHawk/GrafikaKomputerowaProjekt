#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Shader_configure.h"
#include "Renderer.h"
#include "Texture.h"
#include "Camera.h"
#include "load_model_mesh.h"


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

const static int width = 1080;
const static int height = 640;

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

	
	Shader shader("./resources/shaders/Basic.shader");
	shader.Bind();

	shader.SetUniform4f("u_Color", glm::vec4(0.0f, 0.2f, 1.0f, 1.0f));

	Texture texture("./resources/textures/brick.png");
	texture.Bind();							// Binded to 0
	shader.SetUniform1i("u_Texture", 0);	// So 0 also here

	Shader Lshader("./resources/shaders/LightShader.shader");
	Lshader.Bind();

	Lshader.SetUniform4f("u_LightColor", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	glm::vec3 u_Pos = glm::vec3(-1.5f, 20.5f, 0.5f);
	Lshader.SetUniform3f("u_Pos", u_Pos);

	VertexArray LVAO;												// Generates and binds a Vertex Array Object
	VertexBuffer LVBO(vertices, sizeof(vertices));					// Generates, binds and initializes a Vertex Buffer with data given
	VertexBufferLayout Llayout;										// Generates a layout object that stores the Vertex Buffer layout. Describes the way the GPU is to read the vertices data
	Llayout.Push<float>(3);
	LVAO.AddBuffer(LVBO, Llayout);										// The internal function glVertexAttribPointer() binds together Vertex Array and Vertex Buffer, defining the way the buffer stream is read by GPU
	IndexBuffer LEBO(indices, sizeof(indices) / sizeof(GLuint));		// Generates, binds and initializes an Index Array Object with data given. EBO is not binded to VAO in any way, thus it must be binded befr draw call to be used


	shader.Bind();
	glm::vec3 u_LightPos = glm::vec3(-1.5f, 1.5f, 0.5f);
	shader.SetUniform3f("u_LightPos", u_LightPos);
	glm::vec3 u_Cam = glm::vec3(0.5f, 0.5f, 0.5f);
	shader.SetUniform3f("u_Cam", u_Cam);
	shader.SetUniform4f("u_LightColor", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	
	Shader Floorshader("./resources/shaders/Floor.shader");
	Floorshader.Bind();
	Floorshader.SetUniform3f("u_Cam", u_Cam);
	u_Pos = glm::vec3(0.0f, 0.0f, 0.0f);
	Floorshader.SetUniform3f("u_Pos", u_Pos);

	shader.Unbind();
	Lshader.Unbind();
	Floorshader.Unbind();

	LVAO.Unbind();
	LVBO.Unbind();
	LEBO.Unbind();

	Renderer renderer;
	renderer.SetBackgroundColor(glm::vec3(0.07f, 0.13f, 0.17f));
	renderer.EnableBlend();
	renderer.EnableDepthTesting();

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	float r = 0.0f;
	float increment = 0.05f;

	Model kaplica("./resources/objects/kaplica.obj");
	Model model_light("./resources/objects/kw2.obj");
	Model floor("./resources/objects/floor.obj");

	while (!glfwWindowShouldClose(window))
	{
		shader.Bind();
		shader.SetUniform4f("u_Color", glm::vec4(r, 0.0f, 1.0f, 1.0f));
		
		
		camera.Matrix(45.0f, 0.1f, 100.0f, shader, "u_CamMatrix");
		camera.Inputs(window);
		renderer.Clear();
		/*
		renderer.Draw(VAO, EBO, shader);
		
		if (r > 1.0f)
			increment = -0.025f;
		else if (r < 0.0f)
			increment = 0.025f;
		r += increment;
		*/
		
		for (unsigned int i = 0; i < kaplica.num_meshes; ++i)
		{
			glBindTexture(GL_TEXTURE_2D, kaplica.mesh_list[i].tex_handle); // Bind texture for the current mesh.	

			glBindVertexArray(kaplica.mesh_list[i].VAO);
			glDrawElements(GL_TRIANGLES, (GLsizei)kaplica.mesh_list[i].vert_indices.size(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
		Lshader.Bind();
		camera.Matrix(45.0f, 0.1f, 100.0f, Lshader, "u_CamMatrix");
		LVAO.Bind();

		for (unsigned int i = 0; i < model_light.num_meshes; ++i)
		{
			glBindTexture(GL_TEXTURE_2D, model_light.mesh_list[i].tex_handle); // Bind texture for the current mesh.	

			glBindVertexArray(model_light.mesh_list[i].VAO);
			glDrawElements(GL_TRIANGLES, (GLsizei)model_light.mesh_list[i].vert_indices.size(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}

		Floorshader.Bind();
		camera.Matrix(45.0f, 0.1f, 100.0f, Floorshader, "u_CamMatrix");

		for (unsigned int i = 0; i < floor.num_meshes; ++i)
		{
			glBindTexture(GL_TEXTURE_2D, floor.mesh_list[i].tex_handle); // Bind texture for the current mesh.	

			glBindVertexArray(floor.mesh_list[i].VAO);
			glDrawElements(GL_TRIANGLES, (GLsizei)floor.mesh_list[i].vert_indices.size(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}


		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}