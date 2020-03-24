#pragma once
#ifndef CIRCLE_H
#define CIRCLE_H

#include "rigid_body.h"

class circle : public rigid_body
{
public:

	circle(const glm::vec2 & a_position = glm::vec2(0.f), float a_radus = 1.f);

	/*	\brief Sets the radius to the absolute value of the argument.
		\param The new radius as a float
	*/
	void set_radus(float a_radus);
	const float get_radus() const;

	virtual bool check_collision(physics_object* a_object);

	circle & operator = (const circle & a_rhs);

private:
	float m_radus = 0.0f;
	// Position is centre of circle.
};

#endif // !CIRCLE_H

