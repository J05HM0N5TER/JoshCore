#include "shader.h"

void shader::print_shader_error_log(uint shader_id)
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

shader::shader()
{
}

uint shader::create_fragment_shader(const char* fragment_shader)
{

	// Fragment shader
	std::string shader_data;
	std::fstream in_file_stream_frag(fragment_shader, std::ifstream::in);

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
	const char* data = shader_data.c_str();
	// Send in the char* to shader
	glShaderSource(fragment_shader_ID, 1, (const GLchar**)&data, 0);
	// Build!
	glCompileShader(fragment_shader_ID);

	// Did it compile correctly?
	GLint success = GL_FALSE;
	glGetShaderiv(fragment_shader_ID, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		print_shader_error_log(shader_program_ID);
	}

	return fragment_shader_ID;
}

uint shader::create_vertex_shader(const char* vertex_shader)
{
	// Vertex shader
	std::fstream in_file_stream(vertex_shader, std::ifstream::in);

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

	return vertex_shader_ID;
}

uint shader::link_shader_program()
{
	// Link them
	shader_program_ID = glCreateProgram();

	// Attach bot shader by ID and type
	glAttachShader(shader_program_ID, vertex_shader_ID);
	glAttachShader(shader_program_ID, fragment_shader_ID);

	// Finally link the two programs
	glLinkProgram(shader_program_ID);

	GLint success = GL_FALSE;
	glGetProgramiv(shader_program_ID, GL_LINK_STATUS, &success);
	if (success == GL_FALSE)
	{
		assert("shader linking failed");
	}
	
	return shader_program_ID;
}

uint shader::get_shader_program_ID()
{
	return shader_program_ID;
}
