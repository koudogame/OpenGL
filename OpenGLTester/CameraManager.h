#pragma once
#include "Camera.h"
class CameraManager
{
private:
	CameraManager();
	CameraManager(const CameraManager&) = delete;
	CameraManager& operator= (const CameraManager&) = delete;
public:
	static CameraManager* get() { static CameraManager instance; return &instance; }
public:
	~CameraManager();

public:
	//false::V‹K¶¬
	std::pair<bool,Camera*> getCamera(std::string CameraName);

private:
	std::unordered_map<std::string, Camera> camera_;
};
