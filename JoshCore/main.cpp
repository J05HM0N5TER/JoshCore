#include "shader.h"
#include "fly_camera.h"

using uint = unsigned int;

void print_shader_error_log(uint shader_id);

int main() {
	/** Initialise openGL everything **/

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



	/*** Create and 'load' mesh ***/

	const uint verticies_size = 8;
	glm::vec3 verticies[verticies_size]
	{
		glm::vec3(-0.5f, 0.5f, -0.5f),
		glm::vec3(0.5f, 0.5f, -0.5f),
		glm::vec3(-0.5f, -0.5f, -0.5f),
		glm::vec3(0.5f, -0.5f, -0.5f),

		glm::vec3(-0.5f, 0.5f, 0.5f),
		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(-0.5f, -0.5f, 0.5f),
		glm::vec3(0.5f, -0.5f, 0.5f)
	};
	const uint index_buffer_size = 3 * 2 * 6;
	int index_buffer[index_buffer_size]
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
	};

	// Vertex array object
	uint VAO;
	// Vertex buffer object
	uint VBO;
	uint IBO;


	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, verticies_size * sizeof(glm::vec3), verticies, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_size * sizeof(int), index_buffer, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);


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


	while (glfwWindowShouldClose(window) == false &&
		glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		// our game logic and update code goes here!

		model = glm::rotate(model, 0.016f, glm::vec3(0, 1, 0));

		glm::vec4 color = glm::vec4(0.5f);

		main_camera.update(1 / 60.0f, window);

		// Turn shader on
		glUseProgram(main_shader.get_shader_program_ID());

		// Set vaiables
		main_shader.set_uniform_mat4("projection_view_matrix", main_camera.get_projection_view());
		main_shader.set_uniform_mat4("model_matrix", model);
		main_shader.set_uniform_vec4("color", color);
		

		// Clear screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 6);

		glDrawElements(GL_TRIANGLES, index_buffer_size, GL_UNSIGNED_INT, 0);

		// so does our render code!
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &VAO);
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

void print_shader_error_log(uint shader_id)
{
	// Get the length of the error message
	GLint log_length = 0;
	glGetProgramiv(shader_id, GL_INFO_LOG_LENGTH, &log_length);
	// Create the error buffer
	char* log = new char[log_length];
	// Copy the error message
	glGetProgramInfoLog(shader_id, log_length, 0, log);

	// Create the error message
	std::string error_message(log);
	error_message += "SHADER_FAILED_TO_COMPILE";
	printf(error_message.c_str());
	// Clean up anyway
	delete[] log;
}