#pragma once
#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include "circle.h"
#include "aabb.h"
#include "line.h"
#include "glm/glm.hpp"
class collision_manager
{
public:

	//static bool circle_vs_circle(const circle & a_circle_A,
	//	const circle & a_circle_B);

	//static bool aabb_vs_aabb(const aabb & a_aabb_A,
	//	const aabb & a_aabb_B);

	//static bool aabb_vs_circle(const aabb & a_aabb,
	//	const circle & a_circle);

	//static bool circle_vs_line(const circle & a_circle,
	//	const line & a_line);

	//static bool aabb_vs_line(const aabb & a_aabb,
	//	const line & a_line);


	static glm::vec2 circle_vs_circle(const physics_object* a_circle1, const physics_object* a_circle2);
	static glm::vec2 circle_vs_aabb(const physics_object* a_circle, const physics_object* a_aabb);
	static glm::vec2 circle_vs_line(const physics_object* a_circle, const physics_object* a_line);	
	static glm::vec2 aabb_vs_circle(const physics_object* a_circle1, const physics_object* a_circle2);
	static glm::vec2 aabb_vs_aabb(const physics_object* a_circle, const physics_object* a_aabb);
	static glm::vec2 aabb_vs_line(const physics_object* a_circle, const physics_object* a_line);	
	static glm::vec2 line_vs_circle(const physics_object* a_circle1, const physics_object* a_circle2);
	static glm::vec2 line_vs_aabb(const physics_object* a_circle, const physics_object* a_aabb);
	static glm::vec2 line_vs_line(const physics_object* a_circle, const physics_object* a_line);




private:
	static glm::vec2 clamp(const glm::vec2& a_vector_2,
		const glm::vec2& a_min,
		const glm::vec2& a_max);
};

#endif // !COLLISION_MANAGER_H
