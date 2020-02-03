#include "gl_core_4_5.h"
#include "glm.hpp"
#include "glfw3.h"

using uint = unsigned int;

int main() {
	if (glfwInit() == false)
		return -1;

	GLFWwindow* window = glfwCreateWindow(1280, 720,
		"Computer Graphics",
		nullptr, nullptr);

	if (window == nullptr) 
	{
		glfwTerminate();
		return -2;
	}

	glfwMakeContextCurrent(window);

	if (ogl_LoadFunctions() == ogl_LOAD_FAILED) 
	{
		glfwDestroyWindow(window);
		glfwTerminate();
		return -3;
	}


	auto major = ogl_GetMajorVersion();
	auto minor = ogl_GetMinorVersion();
	printf("GL: %i.%i\n", major, minor);

	glm::vec3 verticies[]
	{
		glm::vec3(-0.5f, 0.5f, 0.0f),
		glm::vec3(0.5f, 0.5f, 0.0f),
		glm::vec3(-0.5f, -0.5f, 0.0f),
		glm::vec3(0.5f, 0.5f, 0.0f),
		glm::vec3(-0.5f, -0.5f, 0.0f),
		glm::vec3(0.5f, -0.5f, 0.0f)
	};

	// Vertex array object
	GLuint VAO;
	// Vertex 
	GLuint VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(glm::vec3), &verticies[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	while (glfwWindowShouldClose(window) == false &&
		glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS) 
	{
		// our game logic and update code goes here!

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// so does our render code!
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}