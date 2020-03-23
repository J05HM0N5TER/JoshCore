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

mesh2D primitives2D::circle(const glm::vec4& colour, float radius, int resolution)
{
	return mesh2D();
}

mesh2D primitives2D::triangle(const glm::vec4& colour, float height, float width)
{
	return mesh2D();
}

