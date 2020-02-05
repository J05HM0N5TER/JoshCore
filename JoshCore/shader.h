#pragma once
#ifndef SHADER_H
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
	void print_shader_error_log(uint shader_id);
	uint vertex_shader_ID = UINT_MAX;
	uint fragment_shader_ID = UINT_MAX;
	uint shader_program_ID = UINT_MAX;



public:
	shader();
	uint create_fragment_shader(const char* fragment_shader);
	uint create_vertex_shader(const char* vertex_shader);
	uint link_shader_program();
	uint get_shader_program_ID();

};

#endif // !SHADER_H
