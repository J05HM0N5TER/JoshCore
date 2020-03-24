#pragma once
#ifndef LINE_H
#define LINE_H

#include "physics_object.h"
class line :
	public physics_object
{
public:

	line(const glm::vec2& a_normal = {0,1},
		const float a_distance = 0.0f);

	const glm::vec2 get_normal() const;
	void set_normal(const glm::vec2 & a_normal);

	const float get_distance() const;
	void set_distance(const float a_distance);

	line & operator = (const line & a_rhs);
	bool operator == (const line & a_rhs);
	bool operator != (const line & a_rhs);

private:
	glm::vec2 m_normal = {0,1};
	float m_distance = 0.0f;

};

#endif // !LINE_H
