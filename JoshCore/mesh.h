#pragma once
#ifndef MESH_H
#include <vector>
#include "glm.hpp"
#include "gl_core_4_5.h"

class vertex
{
public:
	vertex(float x, float y, float z)
	{
		position.x = x;
		position.y = y;
		position.z = z;
	}
	const static size_t position_ofset = 0;
	const static size_t position_size = sizeof(glm::vec3);

	glm::vec3 position;
};

class mesh
{
private:
	std::vector<vertex> m_verticies;
	std::vector<int> m_index_order;

public:
	mesh();
	mesh(std::vector<vertex> verticies, std::vector<int> index_order);
	GLsizei get_verticies_length();
	GLsizei get_index_length();
	const void* get_vertex_array();
	const void* get_index_order_array();
	const std::vector<vertex>& get_verticies();
	const std::vector<int> get_index_order();
	void set_verticies(std::vector<vertex>& new_vertices);
	void set_index_order(std::vector<int>& new_index_order);

};

#endif // !MESH_H
