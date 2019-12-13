#pragma once
#include "Model.h"


class TaskManager
{
private:
	TaskManager();
	TaskManager(const TaskManager&) = delete;
	TaskManager& operator=(const TaskManager&) = delete;
public:
	inline static TaskManager* get() { static TaskManager instance; return &instance; }

public:
	~TaskManager();

public:
	template<typename T>
	inline Model* createTask();
	void update();
	void draw();
	void destroy();

private:
	//�^�X�N�I�u�W�F�N�g�Ǘ��p���X�g
	std::list<std::unique_ptr<Model>> object_list_;

	//Update���s�֐����X�g
	std::vector<std::function<void()>> update_list_;
	void firstUpdate();
	void setShape();
	void lastUpdate();
	void checkSurvival();
};

template<typename T>
inline Model * TaskManager::createTask()
{
	object_list_.push_back(std::make_unique<T>());
	object_list_.back().get()->Initialization();
	return object_list_.back().get();
}
