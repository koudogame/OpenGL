#include "stdafx.h"
#include "Box.h"


Box::Box()
{
}


Box::~Box()
{
}

bool Box::init()
{
	setUseCamName("main");
	position_ = glm::vec3((rand() % 50)*0.1F, (rand() % 50)*0.1F, (rand() % 50)*0.1F);
	rotate_ = glm::vec3((rand() % 2), (rand() % 2), (rand() % 2));
	rotate_angle_ = 0.0F;

	return readModel("Resourse/box.obj","Resourse/Wood.png");
}

void Box::firstUpdate()
{
	world_ = glm::translate(position_);
	world_ *= glm::rotate(glm::radians(rotate_angle_++), rotate_);

	GLFWgamepadstate state;
	glfwGetGamepadState(0, &state);
	if (state.buttons[GLFW_GAMEPAD_BUTTON_B] == GLFW_PRESS &&
		old_state_.buttons[GLFW_GAMEPAD_BUTTON_B] == GLFW_RELEASE)
	{
		death();
	}
	old_state_ = state;
}

void Box::destroy()
{
	Model::destroy();
}
