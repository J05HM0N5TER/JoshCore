#include "Camera.h"

void camera::update_projection_view_transform()
{
	this->projection_view_transform = this->projection_transform * this->view_transform;
}

camera::camera()
{
	this->set_perspective(90, 16 / 9.0f, 0.01, 50.0f);
	this->set_look_at(glm::vec3(0, 0, 10), glm::vec3(0), glm::vec3(0, 10, 0));
}

camera::camera(float field_of_view, float aspect_ratio, float near, float far)
{
	this->set_perspective(field_of_view, aspect_ratio, near, far);
}

void camera::update(float delta_time)
{
}

void camera::set_perspective(float field_of_view, float aspect_ratio, float near, float far)
{
	projection_transform = glm::perspective(field_of_view, aspect_ratio, near, far);
	this->update_projection_view_transform();
}

void camera::set_look_at(const glm::vec3& from, const glm::vec3& to, const glm::vec3& up)
{
	view_transform = glm::lookAt(from, to, up);
	world_transform = glm::inverse(view_transform);
	this->update_projection_view_transform();
}

void camera::set_position(const glm::vec3& position)
{
	world_transform[3] = glm::vec4(position, 1);
	view_transform = glm::inverse(world_transform);
	this->update_projection_view_transform();
}

const glm::mat4& camera::get_world_transform()
{
	return this->world_transform;
}

const glm::mat4& camera::get_view()
{
	return this->view_transform;
}

const glm::mat4& camera::get_projection()
{
	return this->projection_transform;
}

const glm::mat4& camera::get_projection_view()
{
	return this->projection_view_transform;
}
