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
	if (object_.size() == 0)
		return;

	for (auto& itr : object_)
	{
		if (itr.second.get() == Model)
		{
			if (itr.second->defRef() <= 0)
			{
				object_.erase(itr.first);
				break;
			}
		}
	}
}
