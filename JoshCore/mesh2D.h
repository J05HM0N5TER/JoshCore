#pragma once
#ifndef MESH2D_H
#define MESH2D_H

#include <vector>
#include "glm.hpp"
#include "gl_core_4_5.h"
#include "shader.h"

class vertex2D
{
public:

	vertex2D(glm::vec3 position, glm::vec4 colour)
		: position{ position, 0 }, colour{ colour }
	{	}

	const static size_t position_size = sizeof(glm::vec4);
	const static size_t position_offset = 0;

	const static size_t colour_size = sizeof(glm::vec4);
	const static size_t colour_offset = position_size + position_offset;

	glm::vec4 position;
	glm::vec4 colour;
};


class mesh2D
{
private:
	// The points in the mesh
	std::vector<vertex2D> m_verticies;
	std::vector<uint> m_indecies;
	// Variables for drawing on screen
	uint VAO, VBO, IBO = UINT_MAX;

	bool setup_complete = false;

public:
	mesh2D();
	~mesh2D();
	mesh2D(std::vector<vertex2D> verticies, std::vector<uint> indecies);
	void setup_mesh();
	void draw(shader& current_shader) const;
	GLsizei get_verticies_length() const;
	const void* get_vertices() const;
	const std::vector<vertex2D>& get_verticies() const;
	void set_verticies(std::vector<vertex2D>& new_vertices);
};

#endif // !MESH2D_H
