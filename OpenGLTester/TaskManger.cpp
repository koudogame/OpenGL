#include "stdafx.h"
#include "TaskManger.h"
#include "Model.h"


TaskManager::TaskManager()
{
	update_list_.push_back(std::bind(&TaskManager::firstUpdate, this));
	update_list_.push_back(std::bind(&TaskManager::setShape, this));
	update_list_.push_back(std::bind(&TaskManager::lastUpdate, this));
	update_list_.push_back(std::bind(&TaskManager::checkSurvival, this));
}


TaskManager::~TaskManager()
{
}

void TaskManager::update()
{
	for (auto& itr : update_list_)
		itr();
}

void TaskManager::draw()
{
	for (auto& itr : object_list_)
		itr->draw();
}

void TaskManager::destroy()
{
	for (auto& itr : object_list_)
		itr->destroy();
}

void TaskManager::firstUpdate()
{
	for (auto& itr : object_list_)
		itr->firstUpdate();
}

void TaskManager::setShape()
{
	for (auto& itr : object_list_)
		itr->moveShape();
}

void TaskManager::lastUpdate()
{
	for (auto& itr : object_list_)
		itr->lastUpdate();
}

void TaskManager::checkSurvival()
{
	auto itr = object_list_.begin();
	auto end = object_list_.end();
	for (; itr != end;)
	{
		if (!itr->get()->isAlive())
		{
			itr->get()->destroy();
			itr = object_list_.erase(itr);
			continue;
		}

		++itr;
	}
}
