#include "mesh.h"

mesh::mesh()
{
}

mesh::mesh(std::vector<vertex> verticies, std::vector<int> index_order)
{
	m_verticies = verticies;
	m_index_order = index_order;
}

int mesh::get_verticies_length()
{
	return m_verticies.size();
}

int mesh::get_index_length()
{
	return m_index_order.size();
}

const void* mesh::get_vertex_array()
{
	return &m_verticies[0];
}

const void* mesh::get_index_order_array()
{
	return &m_index_order[0];
}

const std::vector<vertex>& mesh::get_verticies()
{
	return m_verticies;
}

const std::vector<int> mesh::get_index_order()
{
	return m_index_order;
}

void mesh::set_verticies(std::vector<vertex>& new_vertices)
{
	m_verticies = new_vertices;
}

void mesh::set_index_order(std::vector<int>& new_index_order)
{
	m_index_order = new_index_order;
}
