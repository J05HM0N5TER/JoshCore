#pragma once
#ifndef MESH2D_H
#define MESH2D_H

#include <vector>
#include "glm.hpp"
#include "gl_core_4_5.h"
#include "shader.h"

struct vertex2D
{
	vertex2D(glm::vec2 position, glm::vec3 colour)
		: position{ position, 0, 0 }, colour{ colour, 1 }
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
	std::vector<vertex2D> m_verticies = std::vector<vertex2D>();
	std::vector<uint> m_indecies = std::vector<uint>();
	// Variables for drawing on screen
	uint VAO = UINT_MAX, 
		VBO = UINT_MAX, 
		IBO = UINT_MAX;

	bool setup_complete = false;

public:
	mesh2D();
	~mesh2D();
	mesh2D(std::vector<vertex2D> verticies, std::vector<uint> indecies);
	void setup_mesh();
	GLsizei get_verticies_length() const;
	GLsizei get_indices_length() const;
	const void* get_vertices() const;
	const void* get_indices_array() const;
	const std::vector<vertex2D>& get_verticies() const;
	const std::vector<uint> get_indices() const;
	void set_verticies(std::vector<vertex2D>& new_vertices);
	void set_indices(std::vector<uint>& new_index_order);
	void draw(shader& current_shader) const;
};

#endif // !MESH2D_H
