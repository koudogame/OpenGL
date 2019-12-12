#pragma once
#include "Model.h"
#include "CameraManager.h"

class Box :
	public Model
{
public:
	Box();
	~Box();

public:
	bool init();
	void firstUpdate();
	void destroy();

private:
	Camera camera_;
};

