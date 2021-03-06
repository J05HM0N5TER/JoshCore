#include "mesh.h"

void mesh::setup_mesh()
{
	if (m_verticies.size() == 0)
	{
		throw std::runtime_error("Missing mesh verticies");
	}
	else if (m_indices.size() == 0)
	{
		throw std::runtime_error("Missing mesh indices");
	}

	// Get location to assign data to from GPU
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);

	// Tell GPU what set the following data belongs to
	glBindVertexArray(VAO);


	// Send vertex data
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex) * m_verticies.size(), get_vertices(), GL_STATIC_DRAW);

	// Send index order data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(int), get_indices_array(), GL_STATIC_DRAW);


	// Set vertex settings
	// Position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)vertex::position_offset);

	// Normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE, sizeof(vertex), (void*)vertex::normal_offset);

	// UV
	/*glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)vertex::uv_offset);*/

	// Tell the GPU we are no longer sending it data
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	setup_complete = true;
}

mesh::~mesh()
{
	// Clean up
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &IBO);
	glDeleteBuffers(1, &VAO);
}

mesh::mesh()
{
}

mesh::mesh(std::vector<vertex> verticies, std::vector<int> index_order)
{
	m_verticies = verticies;
	m_indices = index_order;

	setup_mesh();
}

GLsizei mesh::get_verticies_length() const
{
	return GLsizei(m_verticies.size());
}

GLsizei mesh::get_indices_length() const
{
	return GLsizei(m_indices.size());
}

const void* mesh::get_vertices() const
{
	return &m_verticies[0];
}

const void* mesh::get_indices_array() const
{
	return &m_indices[0];
}

const std::vector<vertex>& mesh::get_verticies() const
{
	return m_verticies;
}

const std::vector<int> mesh::get_indices() const
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

void mesh::draw(shader& current_shader, uint& tex) const
{
	if (!setup_complete)
	{
		throw std::runtime_error("Mesh not setup");
	}
	// Tell the GPU what set of data we are using
	glBindVertexArray(VAO);
	glBindTexture(GL_TEXTURE_2D, tex);

	// Tell GPU to draw the m_verticies using the index buffer
	glDrawElements(GL_TRIANGLES, get_indices_length(), GL_UNSIGNED_INT, 0);
}
