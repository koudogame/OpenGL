#pragma once
class Model;

class TaskManager
{
private:
	TaskManager();
	TaskManager(const TaskManager&) = delete;
	TaskManager& operator=(const TaskManager&) = delete;
public:
	inline TaskManager* get() { static TaskManager instance; return &instance; }

public:
	~TaskManager();

public:
	void regist(Model* Obj);
	void unregist(Model* Obj);
	void update();
	void draw();
private:
	std::list<Model*> active_list_;
	std::list<Model*> free_list_;
	std::vector<std::function<void()>> update_list_;
	void firstUpdate();
	void setShape();
	void lastUpdate();
};


