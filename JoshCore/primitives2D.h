#pragma once
#include "mesh2D.h"
class primitives2D
{
public:
	static mesh2D square(const glm::vec4& colour, float width = 1.f, float height = 1.f);
	static mesh2D circle(const glm::vec4& colour, float radius = 1.f, int resolution = 30);
	static mesh2D triangle(const glm::vec4& colour, float height = 1.f, float width = 1.f);
	static mesh2D triangle(const glm::vec4& colour, glm::vec3 point1, glm::vec3 point2, glm::vec3 point3);
};

