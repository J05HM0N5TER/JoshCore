#include "fly_camera.h"

void fly_camera::update(float delta_time)
{

	GLFWwindow* window = glfwGetCurrentContext();
	// Vector to store all the keyboard input to
	glm::vec4 input(0, 0, 0, 0);

	// Get the input and copy to vector (result is 1 if button is down)
	// Left
	input.x -= glfwGetKey(window, GLFW_KEY_A);
	// Right
	input.x += glfwGetKey(window, GLFW_KEY_D);
	// Forwards
	input.z += glfwGetKey(window, GLFW_KEY_W);
	// Backwards
	input.z -= glfwGetKey(window, GLFW_KEY_S);
	// Down
	input.y += glfwGetKey(window, GLFW_KEY_Q);
	// Up
	input.y -= glfwGetKey(window, GLFW_KEY_E);

	// Modify the position based off of the input and the new_speed
	//this->set_position(this->get_world_transform()[3] - (input * speed * delta_time));

	glm::vec4 move_direction = -input.z * world_transform[2] + input.x * world_transform[0] + input.y * world_transform[1];
	glm::normalize(move_direction);

	this->world_transform[3] += (move_direction * speed * delta_time);
	/* MOUSE LOOK */
	double cursor_position_x;
	double cursor_position_y;

	glfwGetCursorPos(window, &cursor_position_x, &cursor_position_y);
	// Calculate the offset from the screens centre this frame
	double delta_x = cursor_position_x - (1280 * 0.5);
	double delta_y = cursor_position_y - (720 * 0.5);
	// Move the cursor back to the centre of the render / window
	// TODO glfwSetInputMode(window , glfw_cursor_disabled)
	// glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPos(window, 1280 * 0.5, 720 * 0.5);

	if (delta_x || delta_y)
	{
		// Identity matrix to accumulate rotation
		auto rotation = glm::mat4(1.0f);
		// Left / Right rotation
		rotation = glm::rotate(rotation, float(angular_speed * delta_time * -delta_x), glm::vec3(view_transform[1]));

		// Up / Down rotation
		rotation = glm::rotate(rotation, float(angular_speed * delta_time * -delta_y), glm::vec3(1.0f, 0.0f, 0.0f));
		// Apply the rotation to the camera
		world_transform = world_transform * rotation;
		// Update PxV
	}


	update_projection_view_transform();
}

void fly_camera::set_speed(float new_speed)
{
	this->speed = new_speed;
}
