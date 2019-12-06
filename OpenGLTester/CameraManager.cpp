#include "stdafx.h"
#include "CameraManager.h"


CameraManager::CameraManager()
{
}


CameraManager::~CameraManager()
{
}

bool CameraManager::regist(std::string CameraName,  Camera const * CameraPtr)
{
	auto find = camera_.find(CameraName);
	if (find != camera_.end())
		return false;
	camera_[CameraName] = CameraPtr;
	return true;
}

void CameraManager::unregist(Camera * CameraPtr)
{
	for (auto& itr : camera_)
	{
		if (itr.second == CameraPtr)
		{
			camera_.erase(itr.first);
			return;
		}
	}
}

Camera const* CameraManager::getCamera(std::string CameraName)const
{
	auto itr = camera_.find(CameraName);

	if (itr != camera_.end())
		return camera_.at(CameraName);

	return nullptr;
}
