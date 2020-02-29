#include "shader.h"
#include "fly_camera.h"
#include <iostream>
#include <time.h>
#include "mesh.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#include <crtdbg.h>
#include "OBJMesh.h"
using uint = unsigned int;

int glm_init(const char* window_name, size_t window_width, size_t window_height);

struct light
{
	glm::vec3 direction;
	glm::vec3 diffuse; 
	glm::vec3 specular;
};

int main() {
	// Check for memory leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	glm_init("JoshCore", 1280, 720);

	GLFWwindow* window = glfwGetCurrentContext();

	/*** Create and 'load' mesh ***/

	mesh quad(
		{
			vertex({ -0.5f, 0,  0.5f }, { 0, 0, 1 }, { 0, 0 }),
			vertex({  0.5f, 0,  0.5f }, { 0, 0, 1 }, { 1, 0 }),
			vertex({ -0.5f, 0, -0.5f }, { 0, 0, 1 }, { 0, 1 }),
			vertex({  0.5f, 0, -0.5f }, { 0, 0, 1 }, { 1, 1 })
		}, 
		{
			1, 2, 0,	// first triangle
			3, 2, 1		// second triangle
		});

	aie::OBJMesh dragon;
	dragon.load("../Models/Dragon.obj");

	/*** Lights ***/
	light main_light;
	main_light.diffuse = { 1, 1, 0 };
	main_light.specular = { 1, 1, 0 };
	glm::vec3 ambient_light = { 0.25, 0.25, 0.25 };

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
	//main_camera.set_position({ 0, 2, 2 });
	glm::mat4 model = glm::mat4(1.0f);


	shader main_shader;
	main_shader.create_fragment_shader("../Shaders/phong.frag");
	main_shader.create_vertex_shader("../Shaders/phong.vert");
	main_shader.link_shader_program();

	// Wire-frame mode
	glPolygonMode(GL_BACK, GL_LINE);

	// Set background colour
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// Used to work out delta-time.
	double previous = glfwGetTime();


	// Disable mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	if (glfwRawMouseMotionSupported())
		glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

	while (glfwWindowShouldClose(window) == false &&
		glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		// Delta-time
		double now = glfwGetTime();
		float delta_time = float(now - previous);
		previous = now;

		main_light.direction = glm::normalize(glm::vec3(glm::cos(now * 2 ), glm::sin(now * 2), 0));
		// Rotate the world
		//model = glm::rotate(model, 0.016f, glm::vec3(0, 1, 0));

		// The colour for the meshes
		glm::vec4 color = glm::vec4(0.5f);

		// Update the camera
		main_camera.update(delta_time);

		// Turn shader on
		glUseProgram(main_shader.get_shader_program_ID());

		// Set variables
		main_shader.set_uniform_vec3("Ia", ambient_light);
		main_shader.set_uniform_vec3("Id", main_light.diffuse);
		main_shader.set_uniform_vec3("Is", main_light.specular);
		main_shader.set_uniform_vec3("LightDirection", main_light.direction);
		main_shader.set_uniform_mat4("projection_view_matrix", main_camera.get_projection_view());
		main_shader.set_uniform_mat4("model_matrix", model);
		main_shader.set_uniform_vec4("colour", color);
		main_shader.set_uniform_mat3("NormalMatrix", glm::inverseTranspose(glm::mat3(model)));

		main_shader.set_uniform_vec3("Ka", glm::vec3(0));
		main_shader.set_uniform_vec3("Kd", { 0.27296f, 0.70272f, 0.6212f });
		main_shader.set_uniform_vec3("Ks", { 0.35f, 0.35f, 0.35f });
		main_shader.set_uniform_float("specularPower", 34.f);

		main_shader.set_uniform_vec3("cameraPosition",
			main_camera.get_position());
		



		// Clear screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//cube.draw(main_shader);
		quad.draw(main_shader, m_texture);
		dragon.draw();

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
