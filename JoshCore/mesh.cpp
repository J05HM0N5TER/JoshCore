#include "mesh.h"

int mesh::get_verticies_length()
{
	return verticies.size();
}

int mesh::get_index_length()
{
	return index_order.size();
}

const vertex& mesh::get_vertex_array()
{
	return verticies[0];
}

const int& mesh::get_index_order_array()
{
	return index_order[0];
}

const std::vector<vertex>& mesh::get_verticies()
{
	return verticies;
}

const std::vector<int> mesh::get_index_order()
{
	return index_order;
}
