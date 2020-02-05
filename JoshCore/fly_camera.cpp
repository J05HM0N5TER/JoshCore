#include "fly_camera.h"

void fly_camera::update(float delta_time, GLFWwindow* window)
{
	// Vector to store all the keyboard input to
	glm::vec4 input(0, 0, 0, 0);

	// Get the input and copy to vector (result is 1 if button is down)
	input.x += glfwGetKey(window, GLFW_KEY_LEFT);
	input.x -= glfwGetKey(window, GLFW_KEY_RIGHT);
	input.z += glfwGetKey(window, GLFW_KEY_UP);
	input.z -= glfwGetKey(window, GLFW_KEY_DOWN);
	 
	// Modify the position based off of the input and the new_speed
	this->set_position(this->get_world_transform()[3] - (input * speed * delta_time));
}

void fly_camera::set_speed(float new_speed)
{
	this->speed = new_speed;
}
