#include "Camera.h"

void camera::update_projection_view_transform()
{
	view_transform = glm::inverse(world_transform);

	this->projection_view_transform = this->projection_transform * this->view_transform;
}

camera::camera()
{
	// Set defaults
	this->set_perspective(90/*degrees*/ * 3.14159f / 180/*Convert to radians*/, 16 / 9.0f/*Wide-screen ratio*/, 0.01f, 50.0f);
	this->set_look_at(glm::vec3(0, 0, 2), glm::vec3(0, 0, 1), glm::vec3(0, 1, 0));
}

camera::camera(float field_of_view, float aspect_ratio, float near, float far)
{
	this->set_perspective(field_of_view, aspect_ratio, near, far);
}

void camera::update(float delta_time) {}

void camera::set_perspective(float field_of_view, float aspect_ratio, float near, float far)
{
	projection_transform = glm::perspective(field_of_view, aspect_ratio, near, far);
	this->update_projection_view_transform();
}

void camera::set_ortho(float left, float right, float bottom, float top)
{
	projection_transform = glm::ortho(left, right, bottom, top);
	this->update_projection_view_transform();
}

void camera::set_look_at(const glm::vec3& from, const glm::vec3& to, const glm::vec3& up)
{
	view_transform = glm::lookAt(from, to, up);
	// Set world transform to inverse view_transform because cameras are backwards
	world_transform = glm::inverse(view_transform);
	this->update_projection_view_transform();
}

void camera::set_position(const glm::vec3& position)
{
	// Get the vector with the positions and sets it
	world_transform[3] = glm::vec4(position, 1);
	// Recalculates the view transform based of the world_transform
	view_transform = glm::inverse(world_transform);
	this->update_projection_view_transform();
}

const glm::vec3& camera::get_position() const
{
	return world_transform[3];
}

const glm::mat4& camera::get_world_transform() const
{
	return this->world_transform;
}

const glm::mat4& camera::get_view() const
{
	return this->view_transform;
}

const glm::mat4& camera::get_projection() const
{
	return this->projection_transform;
}

const glm::mat4& camera::get_projection_view() const
{
	return this->projection_view_transform;
}
