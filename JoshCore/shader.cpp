#include "shader.h"

void shader::print_program_error_log()
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
	error_message += "SHADER_PROGRAM_FAILED_TO_COMPILE";
	printf(error_message.c_str());
	// Clean up anyway
	delete[] log;
	throw std::runtime_error("Shader program compile failed");
}

void shader::print_shader_error_log(uint shader_ID)
{
	// Get the length of the error message
	GLint log_length = 0;
	glGetShaderiv(shader_ID, GL_INFO_LOG_LENGTH, &log_length);
	// Create the error buffer
	char* log = new char[log_length];
	// Copy the error message
	glGetShaderInfoLog(shader_ID, log_length, 0, log);

	// Create the error message
	std::string error_message(log);
	error_message += "SHADER_FAILED_TO_COMPILE";
	printf(error_message.c_str());
	// Clean up anyway
	delete[] log;
	throw std::runtime_error("Shader compile failed");
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

	// Check compile status
	GLint success = GL_FALSE;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		print_shader_error_log(shader_id);
	}

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
	if (vertex_shader_ID == NOT_ASSIGNED)
		throw std::runtime_error("Vertex shader not found");
	if (fragment_shader_ID == NOT_ASSIGNED)
		throw std::runtime_error("Fragment shader not found");

	glAttachShader(shader_program_ID, vertex_shader_ID);
	glAttachShader(shader_program_ID, fragment_shader_ID);

	// Finally link the two programs
	glLinkProgram(shader_program_ID);

	// Check compile status
	GLint log_length = 0;
	glGetProgramiv(shader_program_ID, GL_INFO_LOG_LENGTH, &log_length);

	//check link error
	GLint Success = 0;
	glGetProgramiv(shader_program_ID, GL_LINK_STATUS, &Success);


	//print_program_error_log(shader_program_ID);
	if (Success == GL_FALSE)
	{
		print_program_error_log();
	}

	return shader_program_ID;
}

uint shader::get_shader_program_ID() const
{
	return shader_program_ID;
}

void shader::set_uniform_mat3(const char* variable_name, const glm::mat3& value) const
{
	set_uniform(variable_name, (GLvoid*)&value, UNIFORM_TYPE::MAT3);
}

void shader::set_uniform_mat4(const char* variable_name, const glm::mat4& value) const
{
	set_uniform(variable_name, (GLvoid*)&value, UNIFORM_TYPE::MAT4);
}

void shader::set_uniform_float(const char* variable_name, float value) const
{
	set_uniform(variable_name, (GLvoid*)&value, UNIFORM_TYPE::FLOAT);
}

void shader::set_uniform_vec3(const char* variable_name, const glm::vec3& value) const
{
	set_uniform(variable_name, (GLvoid*)&value, shader::UNIFORM_TYPE::VEC3);
}

void shader::set_uniform_vec4(const char* variable_name, const glm::vec4& value) const
{
	set_uniform(variable_name, (GLvoid*)&value, UNIFORM_TYPE::VEC4);
}

void shader::set_uniform(const char* variable_name, const GLvoid* value, UNIFORM_TYPE varible_type) const
{
	// GEt the uniform location to use to set the variable
	auto uniform_location = glGetUniformLocation(shader_program_ID, variable_name);

	// Set the viable type based on when the paramiter specifies
	switch (varible_type)
	{
	case shader::UNIFORM_TYPE::FLOAT:
		glUniform1fv(uniform_location, 1, (GLfloat*)value);
		break;
	case shader::UNIFORM_TYPE::VEC2:
		glUniform2fv(uniform_location, 1, (GLfloat*)value);
		break;
	case shader::UNIFORM_TYPE::VEC3:
		glUniform3fv(uniform_location, 1, (GLfloat*)value);
		break;
	case shader::UNIFORM_TYPE::VEC4:
		glUniform4fv(uniform_location, 1, (GLfloat*)value);
		break;
	case shader::UNIFORM_TYPE::MAT2:
		glUniformMatrix2fv(uniform_location, 1, false, (GLfloat*)value);
		break;
	case shader::UNIFORM_TYPE::MAT3:
		glUniformMatrix3fv(uniform_location, 1, false, (GLfloat*)value);
		break;
	case shader::UNIFORM_TYPE::MAT4:
		glUniformMatrix4fv(uniform_location, 1, false, (GLfloat*)value);
		break;
	// Bool is transferred like an int and when it is 0 it is false
	case shader::UNIFORM_TYPE::BOOL:
	case shader::UNIFORM_TYPE::INT:
		glUniform1i(uniform_location, GLint(value));
		break;
	case shader::UNIFORM_TYPE::UINT:
		glUniform1ui(uniform_location, GLuint(value));
		break;
	default:
		break;
	}
}
