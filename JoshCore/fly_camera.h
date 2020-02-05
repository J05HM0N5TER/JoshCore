#include "camera.h"
#pragma once
#ifndef FLY_CAMERA_H

class fly_camera : public camera
{
private:
	float speed = 10.f;
	glm::vec3 up;

public:
	void update(float delta_time, GLFWwindow* window);
	void set_speed(float speed);

};

#endif // !FLY_CAMERA_H
