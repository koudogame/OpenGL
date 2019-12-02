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
	//false�œo�^�ς݂œ���̖��O�̃J�������o�^����Ă���
	bool regist(std::string CameraName, Camera const * CameraPtr);
	//nullptr�Ŗ��o�^
	 Camera const* getCamera(std::string CameraName)const;

private:
	std::unordered_map<std::string,  Camera const *> camera_;
};
