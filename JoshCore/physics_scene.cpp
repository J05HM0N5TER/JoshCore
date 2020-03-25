#include "physics_scene.h"
#include <algorithm>
#include <list>
#include <cstdio>
#include "rigid_body.h"

physics_scene::physics_scene()
{
}

physics_scene::~physics_scene()
{
	while (!m_objects.empty())
	{
		m_objects.erase(m_objects.end() - 1);
	}
}

void physics_scene::add_object(physics_object* a_object)
{
	m_objects.push_back(a_object);
}

void physics_scene::remove_object(physics_object* a_object)
{
	auto location = std::find(m_objects.begin(), m_objects.end(), a_object);
	m_objects.erase(location);
	delete a_object;
	a_object = nullptr;
}

void physics_scene::update(float dt)
{
	// update physics at a fixed time step
	accumulatedTime += dt;
	while (accumulatedTime >= m_timeStep)
	{
		for (auto object : m_objects)
		{
			object->fixed_update(m_gravity, m_timeStep);
		}
		accumulatedTime -= m_timeStep;
	}

	static std::list<physics_object*> dirty;

	// Check for collisions
	for (auto object : m_objects)
	{
		for (auto other_object : m_objects)
		{
			if (object == other_object)
				continue;

			if (std::find(dirty.begin(), dirty.end(), object) != dirty.end() &&
				std::find(dirty.begin(), dirty.end(), other_object) != dirty.end())
				continue;

			rigid_body* rb = dynamic_cast<rigid_body*>(other_object);
			if (rb->check_collision(object))
			{
				rb->apply_force_to_object(dynamic_cast<rigid_body*>(object),
					rb->get_velocity() * rb->get_mass());

				dirty.push_back(rb);
				dirty.push_back(other_object);
			}

		}
	}

	dirty.clear();
}

