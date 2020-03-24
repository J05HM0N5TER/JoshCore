#include <crtdbg.h>
#include <iostream>
#include <time.h>
#include "shader.h"
#include "fly_camera.h"
#include "mesh.h"
#include "OBJMesh.h"
#include "texture.h"
#include "mesh2D.h"
#include "primitives2D.h"

void draw(aie::MeshChunk& current_mesh, shader* current_shader, texture* diffuse, texture* normal);
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

	//mesh quad(
	//	{
	//		vertex({ -0.5f, 0,  0.5f }, { 0, 0, 1 }, { 0, 0 }),
	//		vertex({  0.5f, 0,  0.5f }, { 0, 0, 1 }, { 1, 0 }),
	//		vertex({ -0.5f, 0, -0.5f }, { 0, 0, 1 }, { 0, 1 }),
	//		vertex({  0.5f, 0, -0.5f }, { 0, 0, 1 }, { 1, 1 })
	//	},
	//	{
	//		1, 2, 0,	// first triangle
	//		3, 2, 1		// second triangle
	//	});
	mesh2D quad(
		{
			vertex2D({ -0.5f, 0,  0.5f }, {0.5,0.5f,0.5f,1}),
			vertex2D({  0.5f, 0,  0.5f }, {0.5,0.5f,0.5f,1}),
			vertex2D({ -0.5f, 0, -0.5f }, {0.5,0.5f,0.5f,1}),
			vertex2D({  0.5f, 0, -0.5f }, {0.5,0.5f,0.5f,1})
		},
		{
			1, 2, 0,	// first triangle
			3, 2, 1		// second triangle
		});
	quad.setup_mesh();

	/*mesh2D square = primitives2D::square({0.5f,0.5f,0.5f,1.f});
	square.setup_mesh();*/
	//mesh2D triangle = primitives2D::triangle({ 0.5f,0.5f,0.5f,1 }/*Colour*/, 0.1/*Width*/, 0.1);
	mesh2D triangle = primitives2D::triangle({ 0.5f,0.5f,0.5f,1 }/*Colour*/, { -0.001,-0.001,0 }, { 0,0.001f,0 }, { 0.001,0,0 });

	triangle.setup_mesh();
	//Armageddon 

	/** Camera **/
	camera main_camera;
	main_camera.set_ortho(-16, 16, -9, 9);
	main_camera.set_look_at({ 0,0,-1 }, { 0,0,1 }, { 0,1,0 });
	//main_camera.set_position({ 0, 2, 2 });
	glm::mat4 model = glm::mat4(1.0f);
	main_camera.set_position({ 0,0,-1 });

	shader shader2d;
	shader2d.create_fragment_shader("../Shaders/2d.frag");
	shader2d.create_vertex_shader("../Shaders/2d.vert");
	shader2d.link_shader_program();

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
	/*glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	if (glfwRawMouseMotionSupported())
		glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);*/

	while (glfwWindowShouldClose(window) == false &&
		glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		// Delta-time
		double now = glfwGetTime();
		float delta_time = float(now - previous);
		previous = now;

		shader2d.set_uniform_mat4("ProjectionView", main_camera.get_projection_view());

		// The colour for the meshes
		glm::vec4 color = glm::vec4(0.5f);

		// Turn shader on
		glUseProgram(shader2d.get_shader_program_ID());


		// Clear screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//square.draw(shader2d);
		triangle.draw(shader2d);
		//quad.draw(shader2d);

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

void draw(aie::MeshChunk& current_mesh, shader* current_shader, texture* diffuse, texture* normal)
{
	// Get uniform ids
	int program = -1;
	glGetIntegerv(GL_CURRENT_PROGRAM, &program);
	int diffuseTexUniform = glGetUniformLocation(program, "diffuse_texture");
	int normalTexUniform = glGetUniformLocation(program, "normal_texture");

	// Set textures to an ID
	if (diffuseTexUniform >= 0)
		glUniform1i(diffuseTexUniform, 0);
	if (normalTexUniform >= 0)
		glUniform1i(normalTexUniform, 1);

	// Bind textures to correct ID
	glActiveTexture(GL_TEXTURE0);
	if (diffuse->texture_id)
		glBindTexture(GL_TEXTURE_2D, diffuse->texture_id);
	else if (diffuseTexUniform >= 0)
		glBindTexture(GL_TEXTURE_2D, 0);


	glActiveTexture(GL_TEXTURE1);
	if (normal->texture_id)
		glBindTexture(GL_TEXTURE_2D, normal->texture_id);
	else if (normalTexUniform >= 0)
		glBindTexture(GL_TEXTURE_2D, 0);

	/* Simplified view of texture binding
	// Specifying what texture I am setting
	glActiveTexture(GL_TEXTURE0);
	// Set texture
	glBindTexture(GL_TEXTURE_2D, diffuse->texture_id);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, normal->texture_id);
	*/

	// Draw on screen
	current_mesh.Bind();
	glDrawElements(GL_TRIANGLES, current_mesh.indexCount, GL_UNSIGNED_INT, 0);
	current_mesh.Unbind();
}