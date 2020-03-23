#include "mesh2D.h"

mesh2D::mesh2D()
{
}

mesh2D::~mesh2D()
{
	if (setup_complete)
	{
		// Clean up
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &IBO);
		glDeleteBuffers(1, &VAO);
	}
}

mesh2D::mesh2D(std::vector<vertex2D> verticies, std::vector<uint> indecies) :
	m_verticies{ verticies }, m_indecies{ indecies } {}

void mesh2D::setup_mesh()
{
	if (m_verticies.size() == 0)
	{
		throw std::runtime_error("Missing mesh verticies");
	}

	// Get location to assign data to from GPU
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);

	// Tell GPU what set the following data belongs to
	glBindVertexArray(VAO);


	// Send vertex data
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex2D) * m_verticies.size(), get_vertices(), GL_STATIC_DRAW);


	// Set vertex settings
	// Position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(vertex2D), (void*)vertex2D::position_offset);

	// Colour
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE, sizeof(vertex2D), (void*)vertex2D::colour_offset);

	// Tell the GPU we are no longer sending it data
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	setup_complete = true;
}

void mesh2D::draw(shader& current_shader) const
{
}

GLsizei mesh2D::get_verticies_length() const
{
	return m_verticies.size();
}

const void* mesh2D::get_vertices() const
{
	return (void*)&m_verticies[0];
}

const std::vector<vertex2D>& mesh2D::get_verticies() const
{
	return m_verticies;
}

void mesh2D::set_verticies(std::vector<vertex2D>& new_vertices)
{
	m_verticies = new_vertices;
}
