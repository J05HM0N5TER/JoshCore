#pragma once
#ifndef MESH_H
#define MESH_H
#include <vector>
#include "glm.hpp"
#include "gl_core_4_5.h"
#include "shader.h"

class vertex
{
public:
	// What the structure for the vertex is
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
	// The points in the mesh
	std::vector<vertex> m_verticies;
	// How the mesh connects (Index order)
	std::vector<int> m_indices;
	// Varibles for drawing on screen
	uint VAO, VBO, IBO;

	// Sets up the mesh for rendering (sends info to GPU)
	void setup_mesh();

public:
	~mesh();
	mesh() = delete;
	mesh(std::vector<vertex> verticies, std::vector<int> index_order);
	GLsizei get_verticies_length();
	GLsizei get_indices_length();
	const void* get_vertices();
	const void* get_indices_array();
	const std::vector<vertex>& get_verticies();
	const std::vector<int> get_indices();
	void set_verticies(std::vector<vertex>& new_vertices);
	void set_indices(std::vector<int>& new_index_order);

	/*	\brief Renders the mesh on the GPU
		\param current_shader The shader that is being used for this mesh for rendering
	*/
	void draw(shader& current_shader);

};

#endif // !MESH_H
