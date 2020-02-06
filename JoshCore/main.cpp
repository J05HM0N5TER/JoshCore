#include "shader.h"
#include "fly_camera.h"
#include <time.h>
#include "mesh.h"

using uint = unsigned int;

int main() {
	/** Initialise openGL everything **/

	if (glfwInit() == false)
		return -1;

	// Create window
	GLFWwindow* window = glfwCreateWindow(1280, 720,
		"JoshCore",
		nullptr, nullptr);

	// Check if window was created corectly
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



	/*** Create and 'load' mesh ***/

	mesh cube(
		{
		vertex(-0.5f, 0.5f, -0.5f),
		vertex(0.5f, 0.5f, -0.5f),
		vertex(-0.5f, -0.5f, -0.5f),
		vertex(0.5f, -0.5f, -0.5f),

		vertex(-0.5f, 0.5f, 0.5f),
		vertex(0.5f, 0.5f, 0.5f),
		vertex(-0.5f, -0.5f, 0.5f),
		vertex(0.5f, -0.5f, 0.5f)
		}, 
		{
			// Back
			0,1,2,
			1,2,3,

			// Front
			4,5,6,
			5,6,7,

			// Bottom
			2,3,6,
			3,6,7,

			// Right
			1,3,7,
			1,5,7,

			// Left 
			2,0,4,
			2,4,6,

			// Top
			4,0,1,
			4,1,5
		});

	// Vertex array object
	uint VAO;
	// Vertex buffer object
	uint VBO;
	uint IBO;

	// Get location to assign data to from GPU
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);

	// Tell GPU what set the following data belongs to
	glBindVertexArray(VAO);

	// Send vertex data
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, cube.get_verticies_length() * vertex::position_size, cube.get_vertex_array(), GL_STATIC_DRAW);

	// Send index order data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, cube.get_index_length() * sizeof(int), cube.get_index_order_array(), GL_STATIC_DRAW);

	// Set vertex settings
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);

	// Tell the GPU we are no longer sending it data
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	/** Camera **/
	fly_camera main_camera;
	glm::mat4 model = glm::mat4(1.0f);


	shader main_shader;
	//main_shader.create_shader("../Shaders/simple_vertex.glsl", "../Shaders/simple_frag.glsl");
	main_shader.create_fragment_shader("../Shaders/simple_frag.glsl");
	main_shader.create_vertex_shader("../Shaders/simple_vertex.glsl");
	main_shader.link_shader_program();

	// Wire-frame mode
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Set background colour
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	// Used to work out deltatime.
	ULONGLONG previous = GetTickCount64();

	while (glfwWindowShouldClose(window) == false &&
		glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		// Deltatime
		ULONGLONG now = GetTickCount64();
		float delta_time = float(now - previous) / 1000.f;
		previous = now;

		// Rotate the world
		model = glm::rotate(model, 0.016f, glm::vec3(0, 1, 0));

		// The colour for the meshes
		glm::vec4 color = glm::vec4(0.5f);

		// Update the camera
		main_camera.update(delta_time, window);

		// Turn shader on
		glUseProgram(main_shader.get_shader_program_ID());

		// Set vaiables
		main_shader.set_uniform_mat4("projection_view_matrix", main_camera.get_projection_view());
		main_shader.set_uniform_mat4("model_matrix", model);
		main_shader.set_uniform_vec4("color", color);
		

		// Clear screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Tell the GPU what set of data we are using
		glBindVertexArray(VAO);

		// Tell GPU to draw the m_verticies using the index buffer
		glDrawElements(GL_TRIANGLES, cube.get_index_length(), GL_UNSIGNED_INT, 0);

		// Tell GPU to display what it cust calculated
		glfwSwapBuffers(window);
		// Refresh input
		glfwPollEvents();
	}

	// Cleanup
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &VAO);
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}