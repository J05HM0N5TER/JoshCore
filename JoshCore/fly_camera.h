#include "camera.h"
#pragma once
#ifndef FLY_CAMERA_H

class fly_camera : public camera
{
private:
	// How fast the camera should move
	float speed = 10.f;
	float angular_speed = 0.1f;

public:
	
	void update(float delta_time);
	void set_speed(float speed);
};

#endif // !FLY_CAMERA_H
