#include "stdafx.h"
#include "SceneTest.h"
#include "Collision.h"
#include "Camera.h"

//ÉJÉÅÉâÇ∆ëŒè€ÇÃãóó£
const glm::vec3 kOffset = glm::vec3(0.0F,0.0F,30.0F);
const glm::vec2 kLimitAngle = glm::vec2(60.0F, -60.0F);
const float kInputPlayVol = 0.3F;
const float kSpeed = 0.1F;

SceneTest::SceneTest()
{
}


SceneTest::~SceneTest()
{
}

bool SceneTest::init()
{
	if (!model_.init("Dice.obj", "Wood.png"))
		return false;
	if (!target_.init("Dice.obj", "Wood.png"))
		return false;
	position_ = glm::vec3(5.0F, 0.0F, 5.0F);

	rotate_.x = 0.0F;
	rotate_.y = 0.0F;

	setCamPosition();

	target_.setPosition(glm::translate(position_));
	model_.setPosition(glm::mat4(1.0F));
	return true;
}

void SceneTest::setCamPosition()
{
	glm::mat4 turn4 = glm::rotate(glm::radians(rotate_.x), glm::vec3(1.0F, 0.0F, 0.0F));
	turn4 *= glm::rotate(glm::radians(rotate_.y), glm::vec3(0.0F, 1.0F, 0.0F));

	glm::mat3 turn3;

	for (int i = 0; i < 3; ++i)
		turn3[i] = glm::transpose(turn4)[i];

	//Xé≤âÒì]
	cam_position_ = position_ + turn3 * kOffset;

	Camera::Get()->editViewEye(cam_position_);
}

SceneBase * SceneTest::update()
{
	GLFWgamepadstate state;
	glfwGetGamepadState(GLFW_JOYSTICK_1, &state);
	camControl(state);

	glm::vec2 input_vol;
	input_vol.x = state.axes[GLFW_GAMEPAD_AXIS_LEFT_X];
	input_vol.y = state.axes[GLFW_GAMEPAD_AXIS_LEFT_Y];

	input_vol.x = glm::abs(input_vol.x) > kInputPlayVol ? input_vol.x : 0.0F;
	input_vol.y = glm::abs(input_vol.y) > kInputPlayVol ? input_vol.y : 0.0F;

	position_.x += input_vol.x * kSpeed;
	position_.z += input_vol.y * kSpeed;

	target_.setPosition(glm::translate(position_));


	if (Collision::get()->OBBtoOBB(target_.getOBB(), model_.getOBB()))
		int a = 0;

	return this;
}

void SceneTest::camControl(GLFWgamepadstate &State)
{
	glm::vec2 input_vol;
	input_vol.x = State.axes[GLFW_GAMEPAD_AXIS_RIGHT_X];
	input_vol.y = State.axes[GLFW_GAMEPAD_AXIS_RIGHT_Y];

	//Yé≤âÒì]
	rotate_.y += glm::abs(input_vol.x) > kInputPlayVol ? input_vol.x : 0.0F;
	rotate_.x += glm::abs(input_vol.y) > kInputPlayVol ? input_vol.y : 0.0F;
	setCamPosition();
	rotate_.x = rotate_.x > 0 ? glm::min(rotate_.x, kLimitAngle.x) : glm::max(rotate_.x, kLimitAngle.y);
	Camera::Get()->editViewTarget(position_);
}

void SceneTest::draw()
{
	model_.draw();
	target_.draw();
}

void SceneTest::destroy()
{
}
