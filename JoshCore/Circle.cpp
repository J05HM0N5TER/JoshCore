#include "circle.h"
#include "Collision_manager.h"
#include <cmath>

circle::circle(const glm::vec2 & a_position /*= glm::vec2()*/, float a_radus /*= DEFAULT_RADUS*/) :
	rigid_body(shape::circle, a_position),
	m_radus(a_radus)
{}

void circle::set_radus(float a_radus)
{
	m_radus = abs(a_radus);
}

const float circle::get_radus() const
{
	return m_radus;
}

bool circle::check_collision(physics_object* a_object)
{
	return collision_manager::circle_to_circle(*this, (circle&)*a_object);
}

circle & circle::operator=(const circle & a_rhs)
{
	this->m_radus = a_rhs.m_radus;
	this->m_position = a_rhs.m_position;

	return *this;
}

