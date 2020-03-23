#pragma once
#ifndef PHYSICS_OBJECT_H
#define PHYSICS_OBJECT_H
#include "glm/glm.hpp"
#include <vector>

class physics_object
{
public:
	virtual void fixed_update(glm::vec2 gravity, float time_step);
	virtual void debug() = 0;
	virtual void reset_position() {};

};

#endif // !PHYSICS_OBJECT_H
