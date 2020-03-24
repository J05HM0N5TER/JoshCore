#pragma once
#include "physics_object.h"
class rigid_body :
	public physics_object
{
public:
	const glm::vec2& get_position() const { return m_position; }
	const glm::vec2& get_velocity() const { return m_velocity; }
	float get_mass() { return m_mass; }
	void apply_force(const glm::vec2& a_force);
	void apply_force_to_object(rigid_body* a_object, const glm::vec2& a_force);

	~rigid_body() {};

	virtual bool check_collision(physics_object* a_object) = 0;

	virtual void fixed_update(const glm::vec2& a_gravity, float a_time_step);
	virtual void debug();
protected:
	rigid_body(shape a_shape, const glm::vec2& a_position, const glm::vec2& a_velocity, float a_mass);

	rigid_body(shape a_shape, const glm::vec2& a_position);
	glm::vec2 m_position;
	glm::vec2 m_velocity;
	float m_mass;
};

