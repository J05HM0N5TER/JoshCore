#include "aabb.h"
#include <cmath>

const glm::vec2 aabb::DEFAULT_EXTENTS = { 5.0f, 5.0f };

aabb::aabb(
	const glm::vec2 & a_position /*= glm::vec2()*/, 
	const glm::vec2 & a_extents /*= DEFAULT_EXTENTS*/) :
	rigid_body(shape::aabb, a_position),
	m_extents(a_extents)
{
}

const glm::vec2 aabb::get_extents() const
{
	return m_extents;
}

void aabb::set_extents(const glm::vec2 & a_extents)
{
	m_extents = { abs(a_extents.x), abs(a_extents.y) };
}

const float aabb::get_width() const
{
	return m_extents.x;
}

const float aabb::get_height() const
{
	return m_extents.y;
}

const glm::vec2 aabb::get_max() const
{
	return m_position + 0.5f * m_extents;
}

const glm::vec2 aabb::get_min() const
{
	return m_position - 0.5f * m_extents;
}

aabb & aabb::operator=(const aabb & a_rhs)
{
	this->m_extents = a_rhs.m_extents;
	this->m_position = a_rhs.m_position;

	return *this;
}