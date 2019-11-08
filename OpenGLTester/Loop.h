#pragma once
#include "SceneBase.h"
class Loop
{
public:
	Loop();
	~Loop();

public:
	bool init();
	bool update();
	void draw();
	void destroy();

private:
	std::unique_ptr<SceneBase> scene_;
};

