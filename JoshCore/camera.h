#pragma once
#include "glm.hpp"
#ifndef CAMERA_H

class camera
{
private:
	glm::mat4 world_transform;
	glm::mat4 view_transform;
	glm::mat4 projection_transform;
	glm::mat4 projection_view_transform;

	void update_projection_view_transform();

public:
	camera();
	camera(float field_of_view, float aspect_ratio, float near, float far);
	void update(float delta_time);
	void set_perspective(float field_of_view, float aspect_ratio, float near, float far);
	void set_look_at(glm::vec3 from, glm::vec3 to, glm::vec3 up);
	void set_position(glm::vec3 position);
	glm::mat4 get_would_transform();
	glm::mat4 get_view();
	glm::mat4 get_projection();
	
	glm::mat4 get_projection_view();

};


#endif // !CAMERA_H