#include "gl_core_4_5.h"
#include "glm.hpp"
#include "glfw3.h"
#include "ext.hpp"
#include <fstream>
#include <sstream>

using uint = unsigned int;

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

	/** Camera **/
	glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 1), glm::vec3(0), glm::vec3(0, 1, 0));
	glm::mat4 projection = glm::perspective(90.0f, 16 / 9.f, 0.1f, 50.f);
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
		assert("vertex shader failed");
	}


	// Fragment shader
	std::fstream in_file_stream_frag("../Shaders/simple_frag.glal", std::ifstream::in);

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
		assert("fragment shader failed");
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
	if (success = GL_FALSE)
	{
		assert("shader linking failed");
	}




	glm::vec3 verticies[]
	{
		glm::vec3(-0.5f, 0.5f, 0.0f),
		glm::vec3(0.5f, 0.5f, 0.0f),
		glm::vec3(-0.5f, -0.5f, 0.0f),
		glm::vec3(0.5f, 0.5f, 0.0f),
		glm::vec3(-0.5f, -0.5f, 0.0f),
		glm::vec3(0.5f, -0.5f, 0.0f)
	};


	/*** Create and 'load' mesh ***/
	// Vertex array object
	uint VAO;
	// Vertex buffer object
	uint VBO;


	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(glm::vec3), verticies, GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Set background colour
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);


	while (glfwWindowShouldClose(window) == false &&
		glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		// our game logic and update code goes here!

		glm::mat4 pv = projection * view;

		glm::vec4 color = glm::vec4(0.5f);

		// Turn shader on
		glUseProgram(shader_program_ID);

		auto uniform_location = glGetUniformLocation(shader_program_ID, "projection_view_matrix");
		glUniformMatrix4fv(uniform_location, 1, false, glm::value_ptr(pv));
		uniform_location = glGetUniformLocation(shader_program_ID, "model_matrix");
		glUniformMatrix4fv(uniform_location, 1, false, glm::value_ptr(model));
		uniform_location = glGetUniformLocation(shader_program_ID, "color");
		glUniformMatrix4fv(uniform_location, 1, false, glm::value_ptr(model));
		glUniform4fv(uniform_location, 1, glm::value_ptr(color));


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);



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