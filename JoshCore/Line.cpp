#include "line.h"
#include <limits>

line::line(const glm::vec2 & a_normal /*= { 0.0f, 1.0f }*/, 
	const float a_distance /*= 0.0f*/) :
	physics_object(shape::line),
	m_normal(a_normal),
	m_distance(a_distance)
{
	set_normal(m_normal);
}

const glm::vec2 line::get_normal() const
{
	return m_normal;
}

void line::set_normal(const glm::vec2 & a_normal)
{
	if (glm::length(m_normal) < std::numeric_limits<float>::min())
	{
		m_normal = {0,1};
	}
	else
	{
		m_normal = glm::normalize(m_normal);
	}
}

const float line::get_distance() const
{
	return m_distance;
}

void line::set_distance(const float a_distance)
{
	m_distance = a_distance;
}

line & line::operator=(const line & a_rhs)
{
	this->m_normal = a_rhs.m_normal;
	this->m_distance = a_rhs.m_distance;

	return *this;
}
