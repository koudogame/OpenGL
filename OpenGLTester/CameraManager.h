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
	//falseで登録済みで同一の名前のカメラが登録されている
	bool regist(std::string CameraName, Camera const * CameraPtr);
	void unregist(Camera* CameraPtr);
	//nullptrで未登録
	 Camera const* getCamera(std::string CameraName)const;

private:
	std::unordered_map<std::string,  Camera const *> camera_;
};
