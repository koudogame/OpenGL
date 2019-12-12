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
	glm::vec3 eye = { 10.0F,10.0F,10.0F };
	glm::vec3 target = { 0.0F,0.0F,0.0F };
	glm::vec3 up = { 0.0F,1.0F,0.0F };
	CameraManager::get()->regist("main", &camera_);
	camera_.setView(eye, target, up);
	camera_.setProjection(glm::radians(30.0F), 1280.0F / 720.0F, 0.1F, 1000.0F);

	setUseCamName("main");
	return readModel("Resourse/Dice.obj","Resourse/Wood.png");
}

void Box::firstUpdate()
{
	world_ = glm::mat4(1.0F);
}

void Box::destroy()
{
}
