#include "stdafx.h"
#include "TestScene.h"
#include "TaskManger.h"
#include "Model.h"
#include "CameraManager.h"


TestScene::TestScene()
{
}


TestScene::~TestScene()
{
}

bool TestScene::init()
{
	auto box = TaskManager::get()->createTask<Box>();
	dynamic_cast<Box*>(box)->init();
	return true;
}

SceneBase * TestScene::update()
{
	GLFWgamepadstate state;
	static GLFWgamepadstate old_state;
	glfwGetGamepadState(0, &state);
	if (state.buttons[GLFW_GAMEPAD_BUTTON_A] == GLFW_PRESS &&
		old_state.buttons[GLFW_GAMEPAD_BUTTON_A] == GLFW_RELEASE)
	{
		auto box = TaskManager::get()->createTask<Box>();
		dynamic_cast<Box*>(box)->init();
	}
	old_state = state;
	return this;
}

void TestScene::draw()
{
}

void TestScene::destroy()
{
}
