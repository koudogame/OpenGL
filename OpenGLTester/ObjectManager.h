#pragma once
#include "Object.h"

class ObjectManager
{
private:
	ObjectManager();
	ObjectManager(const ObjectManager&) = delete;
	ObjectManager& operator= (const ObjectManager&) = delete;

public:
	static ObjectManager* get() { static ObjectManager instance; return &instance; }

public:
	~ObjectManager();

public:
	Object* getObject(std::string ModelName,std::string TextureName = "");
	void release(std::string ModelName);
	void release(Object* Model);

private:
	std::unordered_map<std::string,std::unique_ptr<Object>> object_;
};

