#include "shader.h"

void shader::check_shader_success()
{
	// Did it compile correctly?
	GLint success = GL_FALSE;
	glGetShaderiv(shader_program_ID, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		// Get the length of the error message
		GLint log_length = 0;
		glGetProgramiv(shader_program_ID, GL_INFO_LOG_LENGTH, &log_length);
		// Create the error buffer
		char* log = new char[log_length];
		// Copy the error message
		glGetProgramInfoLog(shader_program_ID, log_length, 0, log);

		// Create the error message
		std::string error_message(log);
		error_message += "SHADER_FAILED_TO_COMPILE";
		printf(error_message.c_str());
		// Clean up anyway
		delete[] log;
	}
}

uint shader::create_shader(uint shader_type, const char* shader_path)
{
	// The ID of the shader in GPU
	uint shader_id = 0;

	// The string that the data is being stored in
	std::string shader_data;
	// File stream for the shader code
	std::fstream in_file_stream_frag(shader_path, std::ifstream::in);

	std::stringstream frag_string_stream;
	// If opened correctly then copy to the string
	if (in_file_stream_frag.is_open())
	{
		frag_string_stream << in_file_stream_frag.rdbuf();
		shader_data = frag_string_stream.str();
		in_file_stream_frag.close();
	}

	// Get location to put shader code
	shader_id = glCreateShader(shader_type);
	// Convert string to char*
	const char* data = shader_data.c_str();
	// Send in the char* to shader
	glShaderSource(shader_id, 1, (const GLchar**)&data, 0);
	// Build!
	glCompileShader(shader_id);

		check_shader_success();

	return shader_id;
}

shader::shader()
{
}

uint shader::create_fragment_shader(const char* fragment_shader)
{
	fragment_shader_ID = create_shader(GL_FRAGMENT_SHADER, fragment_shader);

	return fragment_shader_ID;
}

uint shader::create_vertex_shader(const char* vertex_shader)
{
	vertex_shader_ID = create_shader(GL_VERTEX_SHADER, vertex_shader);

	return vertex_shader_ID;
}

uint shader::link_shader_program()
{
	if (shader_program_ID != NOT_ASSIGNED)
		return shader_program_ID;

	// Link them
	shader_program_ID = glCreateProgram();

	// Attach shaders that exist
	if (vertex_shader_ID != NOT_ASSIGNED)
		glAttachShader(shader_program_ID, vertex_shader_ID);
	if (fragment_shader_ID != NOT_ASSIGNED)
		glAttachShader(shader_program_ID, fragment_shader_ID);

	// Finally link the two programs
	glLinkProgram(shader_program_ID);

	check_shader_success();

	return shader_program_ID;
}

uint shader::get_shader_program_ID()
{
	return shader_program_ID;
}

void shader::set_uniform_mat4(const char* variable_name, glm::mat4 value)
{
	auto uniform_location = glGetUniformLocation(shader_program_ID, variable_name);
	glUniformMatrix4fv(uniform_location, 1, false, glm::value_ptr(value));
}

void shader::set_uniform_vec4(const char* variable_name, glm::vec4 value)
{
	auto uniform_location = glGetUniformLocation(shader_program_ID, variable_name);
	glUniform4fv(uniform_location, 1, glm::value_ptr(value));
}
