#include "stdafx.h"
#include "CameraManager.h"


CameraManager::CameraManager()
{
}


CameraManager::~CameraManager()
{
}

std::pair<bool, Camera*> CameraManager::getCamera(std::string CameraName)
{
	auto itr = camera_.find(CameraName);

	if (itr != camera_.end())
		return std::make_pair(true, &camera_[CameraName]);

	return std::make_pair(false, &camera_[CameraName]);
}
