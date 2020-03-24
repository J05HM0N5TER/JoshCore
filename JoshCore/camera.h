#pragma once
#include "glm.hpp"
#include "ext.hpp"
#include "glfw3.h"
#ifndef CAMERA_H
#define CAMERA_H

class camera
{
protected:
	// The position the camera is in the world
	glm::mat4 world_transform;
	// Settings for what the view from the camera looks like (FOV, near plane, far plane)
	glm::mat4 view_transform;
	// The position and rotation of the camera
	glm::mat4 projection_transform;
	// The setting put together
	glm::mat4 projection_view_transform;

	// Recalculates the projection view off the view and projection
	void update_projection_view_transform();

public:
	// Default constructor
	camera();

	/*	\brief Constructor with needed camera view settings
		\param field_of_view The field of view for the camera (in radians)
		\param aspect_ratio the dimensions of the cameras view (width / height)
		\param near How far from the camera is the new clipping mask
		\param far How far from the camera is the far clipping mask
	*/
	camera(float field_of_view, float aspect_ratio, float near, float far);

	/*	\brief Template function to be overloaded with the functionality of the camera
		\param delta_time The difference in time since this function was last called
	*/
	virtual void update(float delta_time);

	/*	\brief Sets the settings for view of the camera
		\param field_of_view The field of view for the camera (in radians)
		\param aspect_ratio the dimensions of the cameras view (width / height)
		\param near How far from the camera is the new clipping mask
		\param far How far from the camera is the far clipping mask
	*/
	void set_perspective(float field_of_view, float aspect_ratio, float near, float far);
	
	/*	\brief Sets the settings for view of the camera
		\param field_of_view The field of view for the camera (in radians)
		\param aspect_ratio the dimensions of the cameras view (width / height)
		\param near How far from the camera is the new clipping mask
		\param far How far from the camera is the far clipping mask
	*/
	void set_ortho(float left, float right, float bottom, float top);

	/*	\brief Sets position settings for camera
		\param from The world position that the camera is rendering from
		\param to The vector for the direction that the camera is looking
		\param up The up vector for the direction for where the camera is looking
	*/
	void set_look_at(const glm::vec3 &from, const glm::vec3 &to, const glm::vec3 &up);

	/*	\brief Sets the world position for the camera
		\param position The new world position for the camera
	*/
	void set_position(const glm::vec3 &position);

	/*	\brief Gets the current position of the camera
		\return The camera position in world space
	*/
	const glm::vec3& get_position() const;

	// \return The transform for where is world space the camera is positioned
	const glm::mat4& get_world_transform() const;

	// \return The matrix with all the settings for the position of the camera
	const glm::mat4& get_view() const;

	// \return The settings for how the camera is displaying in a matrix
	const glm::mat4& get_projection() const;
	
	// \return All the settings for the camera to be used in rendering
	const glm::mat4& get_projection_view() const;

};


#endif // !CAMERA_H