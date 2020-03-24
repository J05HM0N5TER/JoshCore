#pragma once
#ifndef AABB_H
#define AABB_H

#include "rigid_body.h"
class aabb : public rigid_body
{
public:

	static const glm::vec2 DEFAULT_EXTENTS;

	aabb(const glm::vec2& a_position = glm::vec2(),
		const glm::vec2& a_extents = DEFAULT_EXTENTS);

	const glm::vec2 get_position() const;
	void set_position(const glm::vec2& a_position);

	const glm::vec2 get_extents() const;
	void set_extents(const glm::vec2& a_extents);

	const float get_width() const;
	const float get_height() const;

	const glm::vec2 get_max() const;
	const glm::vec2 get_min() const;

	aabb& operator = (const aabb & a_rhs);
	bool operator == (const aabb & a_rhs);
	bool operator != (const aabb & a_rhs);

private:
	// Position it the centre of the square

	union
	{
		glm::vec2 m_extents;
		struct
		{
			float m_width;
			float m_height;
		};
	};
};

#endif // !AABB_H
