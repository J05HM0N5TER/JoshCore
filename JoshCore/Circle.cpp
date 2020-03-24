#include "circle.h"
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

const glm::vec2 circle::get_position() const
{
	return m_position;
}

void circle::set_position(const glm::vec2 & a_position)
{
	m_position = a_position;
}

circle & circle::operator=(const circle & a_rhs)
{
	this->m_radus = a_rhs.m_radus;
	this->m_position = a_rhs.m_position;

	return *this;
}

bool circle::operator==(const circle & a_rhs)
{
	return (this->get_radus() == a_rhs.get_radus() &&
		this->get_position() == a_rhs.get_position());
}

bool circle::operator!=(const circle & a_rhs)
{
	return !(*this == a_rhs);
}



