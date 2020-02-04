#include "fly_camera.h"

void fly_camera::update(float delta_time, GLFWwindow* window)
{
	glm::vec4 input(0, 0, 0, 0);

	input.x += glfwGetKey(window, GLFW_KEY_LEFT);
	input.x -= glfwGetKey(window, GLFW_KEY_RIGHT);
	input.z += glfwGetKey(window, GLFW_KEY_UP);
	input.z -= glfwGetKey(window, GLFW_KEY_DOWN);

		this->set_position(this->get_world_transform()[3] - (input * speed));
}

void fly_camera::set_speed(float speed)
{
}
