#pragma once
#ifndef SHADER_H
#define SHADER_H
#include "ext.hpp"
#include <fstream>
#include <sstream>
#include "glm.hpp"
#include "gl_core_4_5.h"
#include "glfw3.h"

using uint = unsigned int;
class shader
{
private:
	// Value that the shaders will have if they don't exist
	const uint NOT_ASSIGNED = UINT_MAX;
	// The ID of the vertex shader on the GPU
	uint vertex_shader_ID = UINT_MAX;
	// The ID of the fragment shader on the GPU
	uint fragment_shader_ID = UINT_MAX;
	// The ID of the shader program on the GPU
	uint shader_program_ID = UINT_MAX;

	// Function to print the error log on the shader program
	void print_program_error_log();
	void print_shader_error_log(uint shader_ID);

	uint create_shader(uint shader_type, const char* shader_path);

public:

	// Used to specify what data type in the set_uniform
	static enum class UNIFORM_TYPE : char
	{
		FLOAT,
		VEC2,
		VEC3,
		VEC4,
		MAT2,
		MAT3,
		MAT4,
		INT,
		UINT,
		BOOL
	};

	// Constructor
	shader();

	/*	\brief compiles a file to a fragment shader on GPU
		\param fragment_shader The path to the fragment shader code file
		\return The ID of the fragment shader
		\warning If the compile fails it will print errors to command window 
	*/
	uint create_fragment_shader(const char* fragment_shader);

	/*	\brief compiles a file to a vertex shader on GPU
		\param fragment_shader The path to the vertex shader code file
		\return The ID of the vertex shader
		\warning If the compile fails it will print errors to command window 
	*/
	uint create_vertex_shader(const char* vertex_shader);

	/*	\brief Links the different shaders that have been created together into a shader program
		\return The ID for the shader program
	*/
	uint link_shader_program();

	/*	Return the ID of the created ID
		\warning If UINT_MAX then the shader program has not been made yet
	*/
	uint get_shader_program_ID();

	/*	\brief Sets a matrix 4 on the shader program
		\param variable_name The name of the variable that you are setting
		\param value The value that you are setting it to
	*/
	void set_uniform_mat3(const char* variable_name, const glm::mat3& value);

	/*	\brief Sets a matrix 4 on the shader program
		\param variable_name The name of the variable that you are setting
		\param value The value that you are setting it to
	*/
	void set_uniform_mat4(const char* variable_name, const glm::mat4& value);

	/*	\brief Sets a float on the shader program
		\param variable_name The name of the variable that you are setting
		\param value The value that you are setting it to
	*/
	void set_uniform_float(const char* variable_name, float value);
	
	/*	\brief Sets a vector 3 on the shader program
		\param variable_name The name of the variable that you are setting
		\param value The value that you are setting it to
	*/
	void set_uniform_vec3(const char* variable_name, const glm::vec3& value);

	/*	\brief Sets a vector 4 on the shader program
		\param variable_name The name of the variable that you are setting
		\param value The value that you are setting it to
	*/
	void set_uniform_vec4(const char* variable_name, const glm::vec4& value);

	/*	\brief Sets a variable on the shader program
		\param variable_name The name of the variable that you are setting
		\param value The value that you are setting it to cast to a GLvoid*
		\param varible_type The data type that the variable you are setting is
	*/
	void set_uniform(const char* variable_name, const GLvoid* value, UNIFORM_TYPE varible_type);
};

#endif // !SHADER_H
