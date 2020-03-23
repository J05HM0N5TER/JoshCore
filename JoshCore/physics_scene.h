#pragma once
#include "physics_object.h"
class physics_scene
{
public:
	physics_scene();
	~physics_scene();

	void add_object(physics_object* actor);
	void remove_object(physics_object* actor);
	void update(float dt); 

	void set_gravity(const glm::vec2 gravity) { m_gravity = gravity; }
	glm::vec2 get_gravity() const { return m_gravity; }

	void set_time_step(const float timeStep) { m_timeStep = timeStep; }
	float get_time_step() const { return m_timeStep; }

protected:
	glm::vec2 m_gravity;
	float m_timeStep;
	std::vector<physics_object*> m_objects;
};

