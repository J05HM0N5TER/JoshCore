#include "camera.h"
#pragma once
#ifndef FLY_CAMERA_H

class fly_camera : camera
{
private:
	float speed;
	glm::vec3 up;

public:
	void update();
	void set_speed(float speed);

};

#endif // !FLY_CAMERA_H
