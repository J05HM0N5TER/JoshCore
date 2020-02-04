#include "gl_core_4_5.h"
#include "glm.hpp"
#include "glfw3.h"
#include "ext.hpp"
#include <fstream>
#include <sstream>
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


	/*** Load shaders ***/
	uint vertex_shader_ID = 0;
	uint fragment_shader_ID = 0;
	uint shader_program_ID = 0;


	// Vertex shader
	std::fstream in_file_stream("../Shaders/simple_vertex.glsl", std::ifstream::in);

	std::string shader_data;
	std::stringstream string_stream;
	if (in_file_stream.is_open())
	{
		string_stream << in_file_stream.rdbuf();
		shader_data = string_stream.str();
		in_file_stream.close();
	}

	// Get location to put shader code
	vertex_shader_ID = glCreateShader(GL_VERTEX_SHADER);
	// Convert string to char*
	const char* data = shader_data.c_str();
	// Send in the char* to shader
	glShaderSource(vertex_shader_ID, 1, (const GLchar**)&data, 0);
	// Build!
	glCompileShader(vertex_shader_ID);

	// Did it compile correctly?
	GLint success = GL_FALSE;
	glGetShaderiv(vertex_shader_ID, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		print_shader_error_log(shader_program_ID);
	}


	// Fragment shader
	std::fstream in_file_stream_frag("../Shaders/simple_frag.glsl", std::ifstream::in);

	std::stringstream frag_string_stream;
	if (in_file_stream_frag.is_open())
	{
		frag_string_stream << in_file_stream_frag.rdbuf();
		shader_data = frag_string_stream.str();
		in_file_stream_frag.close();
	}

	// Get location to put shader code
	fragment_shader_ID = glCreateShader(GL_FRAGMENT_SHADER);
	// Convert string to char*
	data = shader_data.c_str();
	// Send in the char* to shader
	glShaderSource(fragment_shader_ID, 1, (const GLchar**)&data, 0);
	// Build!
	glCompileShader(fragment_shader_ID);

	// Did it compile correctly?
	success = GL_FALSE;
	glGetShaderiv(fragment_shader_ID, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		print_shader_error_log(shader_program_ID);
	}

	// Link them
	shader_program_ID = glCreateProgram();

	// Attach bot shader by ID and type
	glAttachShader(shader_program_ID, vertex_shader_ID);
	glAttachShader(shader_program_ID, fragment_shader_ID);

	// Finally link the two programs
	glLinkProgram(shader_program_ID);

	success = GL_FALSE;
	glGetProgramiv(shader_program_ID, GL_LINK_STATUS, &success);
	if (success == GL_FALSE)
	{
		assert("shader linking failed");
	}


	// Wire-frame mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

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
		glUseProgram(shader_program_ID);

		auto uniform_location = glGetUniformLocation(shader_program_ID, "projection_view_matrix");
		glUniformMatrix4fv(uniform_location, 1, false, glm::value_ptr(main_camera.get_projection_view()));
		uniform_location = glGetUniformLocation(shader_program_ID, "model_matrix");
		glUniformMatrix4fv(uniform_location, 1, false, glm::value_ptr(model));
		uniform_location = glGetUniformLocation(shader_program_ID, "color");
		glUniformMatrix4fv(uniform_location, 1, false, glm::value_ptr(model));
		glUniform4fv(uniform_location, 1, glm::value_ptr(color));


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