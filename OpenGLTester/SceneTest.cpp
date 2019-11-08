#include "stdafx.h"
#include "SceneTest.h"


SceneTest::SceneTest()
{
}


SceneTest::~SceneTest()
{
}

bool SceneTest::init()
{
	if (!model_.init("Desk.obj", "cheker.png"))
		return false;
	return true;
}

SceneBase * SceneTest::update()
{
	static float angle = 0;
	glm::mat4 position = glm::rotate(glm::radians(angle++), glm::vec3(0.0F, 1.0F, 0.0F));
	model_.setPosition(position);
	return this;
}

void SceneTest::draw()
{
	model_.SendSheder();
	model_.draw();
}

void SceneTest::destroy()
{
}
