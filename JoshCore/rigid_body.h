#pragma once
#include "physics_object.h"
class rigid_body :
	public physics_object
{
public:
	glm::vec2 m_position;
	glm::vec2 m_vector;
	float mass;
	void apply_force();

protected:
	rigid_body(shape a_shape, const glm::vec2& a_position)
		: physics_object(a_shape), m_position(a_position) {};
};

