#include "stdafx.h"
#include "Loop.h"
#include "TestScene.h"
#include "TaskManger.h"
Loop::Loop()
{
}


Loop::~Loop()
{
}

bool Loop::init()
{
	scene_ = std::make_unique<TestScene>();
	if (!scene_->init())
		return false;
	return true;
}

bool Loop::update()
{
	TaskManager::get()->update();
	auto temp = scene_->update();
	if (temp == nullptr)
		return false;
	else if (temp != scene_.get())
	{
		scene_->destroy();
		scene_.reset(temp);
		if (!scene_->init())
			return false;
	}
	return true;
}

void Loop::draw()
{
	TaskManager::get()->draw();
	scene_->draw();
}

void Loop::destroy()
{
	scene_->destroy();
}
