#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H
#include "glfw3.h"

class texture
{
public:

	texture(const char* texture_path);
	texture() = delete;

	unsigned int texture_id;
};

#endif // !TEXTURE_H
