#include "physics_scene.h"
#include <algorithm>

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
	static float accumulatedTime = 0.0f;
	accumulatedTime += dt;
	while (accumulatedTime >= m_timeStep)
	{
		for (auto object : m_objects)
		{
			object->fixed_update(m_gravity, m_timeStep);
		}
		accumulatedTime -= m_timeStep;
	}
}

