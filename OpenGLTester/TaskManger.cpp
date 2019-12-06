#include "stdafx.h"
#include "TaskManger.h"
#include "Model.h"


TaskManager::TaskManager()
{
	update_list_.push_back(std::bind(&TaskManager::firstUpdate, this));
	update_list_.push_back(std::bind(&TaskManager::setShape, this));
	update_list_.push_back(std::bind(&TaskManager::lastUpdate, this));
}


TaskManager::~TaskManager()
{
}

void TaskManager::regist(Model* Obj)
{
	object_list_.push_back(Obj);
}

void TaskManager::unregist(Model* Obj)
{
	auto itr = object_list_.begin(),end = object_list_.end();

	for (; itr != end; ++itr)
	{
		if (*itr == Obj)
			break;
	}
	if (itr == end)
		return;
	object_list_.erase(itr);
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
