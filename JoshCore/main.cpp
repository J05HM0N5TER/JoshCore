#include "shader.h"
#include "fly_camera.h"
#include <iostream>
#include <time.h>
#include "mesh.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#include <crtdbg.h>
using uint = unsigned int;

int glm_init(const char* window_name, size_t window_width, size_t window_height);

int main() {
	// Check for memory leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	glm_init("JoshCore", 1280, 720);

	GLFWwindow* window = glfwGetCurrentContext();

	/*** Create and 'load' mesh ***/

	mesh square(
		{
			vertex({ -0.5f, 0.5f, 0 }, { 0, 0, 1 }, { 0, 0 }),
			vertex({ 0.5f, 0.5f, 0 }, { 0, 0, 1 }, { 1,0 }),
			vertex({ -0.5f, -0.5f, 0 }, { 0, 0, 1 }, { 0, 1 }),
			vertex({ 0.5f, -0.5f, 0 }, { 0, 0, 1 }, { 1, 1 })
		}, 
		{
			1, 2, 0,	// first triangle
			3, 2, 1		// second triangle
		});

	uint m_texture;
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	int width, height, nrChannels;
	unsigned char* data = stbi_load("../images/test.jpg", &width, &height, &nrChannels, 0);
	std::cout << " width: " << width << " height: " << height << " channel count: " << nrChannels << std::endl;

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, nrChannels != 4 ? GL_RGB : GL_RGBA, width, height, 0, nrChannels != 4 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, data);
	}
	else
	{
		printf("Failed to load texture\n");
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // GL_LINEAR SAMPLES texels
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // GL_NEARESTS RETURNS just closest pixel

	//glDeleteTextures(1, &m_texture));

	stbi_image_free(data);


	/** Camera **/
	fly_camera main_camera;
	glm::mat4 model = glm::mat4(1.0f);


	shader main_shader;
	main_shader.create_fragment_shader("../Shaders/phong.frag");
	main_shader.create_vertex_shader("../Shaders/phong.vert");
	main_shader.link_shader_program();

	// Wire-frame mode
	glPolygonMode(GL_BACK, GL_LINE);

	// Set background colour
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	// Used to work out delta-time.
	ULONGLONG previous = GetTickCount64();

	// Disable mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	if (glfwRawMouseMotionSupported())
		glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

	while (glfwWindowShouldClose(window) == false &&
		glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		// Delta-time
		ULONGLONG now = GetTickCount64();
		float delta_time = float(now - previous) / 1000.f;
		previous = now;

		// Rotate the world
		model = glm::rotate(model, 0.016f, glm::vec3(0, 1, 0));

		// The colour for the meshes
		glm::vec4 color = glm::vec4(0.5f);

		// Update the camera
		main_camera.update(delta_time);

		// Turn shader on
		glUseProgram(main_shader.get_shader_program_ID());

		// Set variables
		main_shader.set_uniform_mat4("projection_view_matrix", main_camera.get_projection_view());
		main_shader.set_uniform_mat4("model_matrix", model);
		main_shader.set_uniform_vec4("colour", color);


		// Clear screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//cube.draw(main_shader);
		square.draw(main_shader, m_texture);

		// Tell GPU to display what it just calculated
		glfwSwapBuffers(window);
		// Refresh input
		glfwPollEvents();
	}

	// Clean-up
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

int glm_init(const char* window_name, size_t window_width, size_t window_height)
{
	/** Initialise openGL everything **/

	if (glfwInit() == false)
		return -1;

	// Create window
	GLFWwindow* window = glfwCreateWindow(window_width, window_height,
		window_name,
		nullptr, nullptr);

	// Check if window was created correctly
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

	return 0;
}
