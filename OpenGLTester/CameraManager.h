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
	//false‚Å“o˜^Ï‚İ‚Å“¯ˆê‚Ì–¼‘O‚ÌƒJƒƒ‰‚ª“o˜^‚³‚ê‚Ä‚¢‚é
	bool regist(std::string CameraName, Camera const * CameraPtr);
	//nullptr‚Å–¢“o˜^
	 Camera const* getCamera(std::string CameraName)const;

private:
	std::unordered_map<std::string,  Camera const *> camera_;
};
