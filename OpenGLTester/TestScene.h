#pragma once
#include "SceneBase.h"
class TestScene:public SceneBase
{
public:
	TestScene();
	~TestScene();

public:
	bool init();
	SceneBase* update();
	void draw();
	void destroy();
};

