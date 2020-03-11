#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H
#include "glfw3.h"

class texture
{
public:

	texture(const char* texture_path);
	texture() = delete;

	unsigned int texture_id = 0;
};

#endif // !TEXTURE_H
