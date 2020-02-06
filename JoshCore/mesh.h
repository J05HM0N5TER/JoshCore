#pragma once
#ifndef MESH_H
#include <vector>
#include "glm.hpp"

struct vertex
{
	const int position_position = 0;

	glm::vec3 position;
};

class mesh
{
private:
	std::vector<vertex> verticies;
	std::vector<int> index_order;

public:

	int get_verticies_length();
	int get_index_length();
	const vertex& get_vertex_array();
	const int& get_index_order_array();
	const std::vector<vertex>& get_verticies();
	const std::vector<int> get_index_order();

};

#endif // !MESH_H
