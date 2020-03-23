#include "primitives2D.h"
#include <vector>
mesh2D primitives2D::square(const glm::vec4& colour, float width, float height)
{
	glm::vec3 normal = { 0,0,-1 };
	float z = 0;
	float w = width / 2;
	float h = height / 2;
	std::vector<vertex2D> vectors;
	vectors.push_back({ {-w, -h, w },colour });
	vectors.push_back({ {-w, h, w }, colour });
	vectors.push_back({ {w, -h, w }, colour });
	vectors.push_back({ {w, h, w }, colour });

	std::vector<uint> buffer =
	{
		0,1,2,
		1,2,3
	};

	return mesh2D(vectors, buffer);
}

mesh2D primitives2D::circle(const glm::vec4& colour, float radius, int segments)
{
	std::vector<vertex2D> verticies = std::vector<vertex2D>();
	std::vector<uint> indecies = std::vector<uint>();
	float previous_x, previous_y, x, y;
	float angle;
	float segment_size = 360.f / segments;

	previous_x = 0.5, previous_y = 0.6;

	for (angle = 0.f; angle < 361.0f; angle += segment_size)
	{
		x = previous_x + sin(angle) * radius;
		y = previous_y + cos(angle) * radius;
		verticies.push_back({ {x,y,0},colour });
	}

	for (size_t i = 1; i < segments - 1; i++)
	{
		indecies.push_back(0);
		indecies.push_back(i);
		indecies.push_back(i + 1);
	}

	return mesh2D(verticies, indecies);
}

mesh2D primitives2D::triangle(const glm::vec4& colour, float height, float width)
{
	std::vector<vertex2D> verticies = std::vector<vertex2D>();
	verticies.push_back({ {height / 2, 0, 0}, colour });
	verticies.push_back({ {-height / 2, -width / 2, 0}, colour });
	verticies.push_back({ {-height / 2, width / 2, 0}, colour });
	return mesh2D(verticies, { 0,1,2 });
}

mesh2D primitives2D::triangle(const glm::vec4& colour, glm::vec3 point1, glm::vec3 point2, glm::vec3 point3)
{
	std::vector<vertex2D> verticies = std::vector<vertex2D>();
	verticies.push_back({ point1, colour });
	verticies.push_back({ point2, colour });
	verticies.push_back({ point3, colour });
	return mesh2D(verticies, { 0,1,2 });
}

