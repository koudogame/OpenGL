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
	if (free_list_.empty())
	{
		active_list_.push_back(Obj);
		return;
	}

	active_list_.splice(active_list_.begin(), free_list_, free_list_.begin());
	active_list_.front() = Obj;
}

void TaskManager::unregist(Model* Obj)
{
	auto itr = active_list_.begin(),end = active_list_.end();

	for (; itr != end; ++itr)
	{
		if (*itr == Obj)
			break;
	}
	if (itr == end)
		return;
	free_list_.splice(free_list_.begin(), active_list_, itr);
}

void TaskManager::update()
{
	for (auto& itr : update_list_)
		itr();
}

void TaskManager::draw()
{
	for (auto& itr : active_list_)
		itr->draw();
}

void TaskManager::firstUpdate()
{
	for (auto& itr : active_list_)
		itr->firstUpdate();
}

void TaskManager::setShape()
{
	for (auto& itr : active_list_);
	//TODO:shpae‚ÌXVˆ—
}

void TaskManager::lastUpdate()
{
	for (auto& itr : active_list_)
		itr->lastUpdate();
}
