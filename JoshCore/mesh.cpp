#include "mesh.h"

void mesh::setup_mesh()
{
	// Get location to assign data to from GPU
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);

	// Tell GPU what set the following data belongs to
	glBindVertexArray(VAO);


	// Send vertex data
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, get_verticies_length() * vertex::position_size, get_vertices(), GL_STATIC_DRAW);

	// Send index order data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, get_indices_length() * sizeof(int), get_indices_array(), GL_STATIC_DRAW);


	// Set vertex settings
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);

	// Tell the GPU we are no longer sending it data
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

mesh::~mesh()
{
	// Clean up
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &IBO);
	glDeleteBuffers(1, &VAO);
}

mesh::mesh(std::vector<vertex> verticies, std::vector<int> index_order)
{
	m_verticies = verticies;
	m_indices = index_order;

	setup_mesh();
}

GLsizei mesh::get_verticies_length()
{
	return GLsizei(m_verticies.size());
}

GLsizei mesh::get_indices_length()
{
	return GLsizei(m_indices.size());
}

const void* mesh::get_vertices()
{
	return &m_verticies[0];
}

const void* mesh::get_indices_array()
{
	return &m_indices[0];
}

const std::vector<vertex>& mesh::get_verticies()
{
	return m_verticies;
}

const std::vector<int> mesh::get_indices()
{
	return m_indices;
}

void mesh::set_verticies(std::vector<vertex>& new_vertices)
{
	m_verticies = new_vertices;
}

void mesh::set_indices(std::vector<int>& new_index_order)
{
	m_indices = new_index_order;
}

void mesh::draw(shader& current_shader)
{
	// Tell the GPU what set of data we are using
	glBindVertexArray(VAO);

	// Tell GPU to draw the m_verticies using the index buffer
	glDrawElements(GL_TRIANGLES, get_indices_length(), GL_UNSIGNED_INT, 0);
}
