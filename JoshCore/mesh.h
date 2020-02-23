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
	vertex(float x, float y, float z, float u, float v)
	{
		position.x = x;
		position.y = y;
		position.z = z;
		uv.x = u;
		uv.y = v;
	}
	vertex(glm::vec3 position, glm::vec2 uv)
	{
		this->position = position;
		this->uv = uv;
	}
	const static size_t position_offset = 0;
	const static size_t position_size = sizeof(glm::vec3);
	const static size_t uv_size = sizeof(glm::vec2);
	const static size_t uv_offset = position_size + position_offset;

	glm::vec3 position;
	glm::vec2 uv;
};

class mesh
{
private:
	// The points in the mesh
	std::vector<vertex> m_verticies;
	// How the mesh connects (Index order)
	std::vector<int> m_indices;
	// Variables for drawing on screen
	uint VAO, VBO, IBO;

	// Sets up the mesh for rendering (sends info to GPU)
	void setup_mesh();

	bool setup_complete = false;

public:
	~mesh();
	mesh();
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
	void draw(shader& current_shader, uint& tex);

};

#endif // !MESH_H
