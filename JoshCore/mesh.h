#pragma once
#ifndef MESH_H
#include <vector>
#include "glm.hpp"

class vertex
{
public:
	vertex(float x, float y, float z)
	{
		position.x = x;
		position.y = y;
		position.z = z;
	}
	const static int position_ofset = 0;
	const static int position_size = sizeof(glm::vec3);

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
	int get_verticies_length();
	int get_index_length();
	const void* get_vertex_array();
	const void* get_index_order_array();
	const std::vector<vertex>& get_verticies();
	const std::vector<int> get_index_order();
	void set_verticies(std::vector<vertex>& new_vertices);
	void set_index_order(std::vector<int>& new_index_order);

};

#endif // !MESH_H
