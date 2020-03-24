#include "rigid_body.h"

void rigid_body::apply_force(const glm::vec2& a_force)
{
	m_velocity += a_force / m_mass;
}

void rigid_body::apply_force_to_object(rigid_body* a_object, const glm::vec2& a_force)
{
	a_object->apply_force(a_force);
	this->apply_force(-a_force);
}

void rigid_body::fixed_update(const glm::vec2& a_gravity, float a_time_step)
{
	apply_force(a_gravity * m_mass * a_time_step);

	m_position += m_velocity * a_time_step;
}

void rigid_body::debug()
{
}

rigid_body::rigid_body(shape a_shape, const glm::vec2& a_position, const glm::vec2& a_velocity, float a_mass)
	: physics_object(a_shape), m_position(a_position), m_mass(a_mass), m_velocity(a_velocity)
{
}

rigid_body::rigid_body(shape a_shape, const glm::vec2& a_position)
	: physics_object(a_shape), m_position(a_position) {}
