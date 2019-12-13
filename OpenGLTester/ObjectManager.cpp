#include "stdafx.h"
#include "ObjectManager.h"


ObjectManager::ObjectManager()
{
}


ObjectManager::~ObjectManager()
{
}

Object * ObjectManager::getObject(std::string ModelName,std::string TextureName)
{
	auto find = object_.find(ModelName);

	if (find != object_.end())
	{
		find->second->addRef();
		return find->second.get();
	}

	Object* obj = new Object;
	if (!obj->createVertexData(ModelName))
	{
		delete obj;
		return nullptr;
	}
	if (TextureName != "")
		obj->loadTexture(TextureName);
	obj->addRef();
	object_.insert(std::make_pair(ModelName, std::unique_ptr<Object>(obj)));
	return obj;
}

void ObjectManager::release(std::string ModelName)
{
	auto find = object_.find(ModelName);

	if (find == object_.end())
		return;

	if (find->second->defRef() <= 0)
		object_.erase(ModelName);
}

void ObjectManager::release(Object * Model)
{
	auto itr = object_.begin();
	auto end = object_.end();
	for (; itr != end; ++itr)
		if (itr->second.get() == Model)
			break;

	if (itr == end)
		return;

	if (itr->second->defRef() <= 0)
		object_.erase(itr->first);
}
