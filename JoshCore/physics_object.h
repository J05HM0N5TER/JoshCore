#pragma once
#ifndef PHYSICS_OBJECT_H
#define PHYSICS_OBJECT_H
#include "glm/glm.hpp"
#include <vector>
enum class shape : char
{
	circle = 0,
	aabb,
	line,
	count
};

class physics_object
{
protected:
	shape shape_type;
	physics_object(shape a_shape) : shape_type{ a_shape } {}

public:
	virtual void fixed_update(glm::vec2 gravity, float time_step);
	virtual void debug() = 0;
	virtual void reset_position() {};

};

#endif // !PHYSICS_OBJECT_H
