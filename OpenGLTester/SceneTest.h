#pragma once
#include "SceneBase.h"
#include "Model.h"

class SceneTest :public SceneBase
{
public:
	SceneTest();
	~SceneTest();

public:
	bool init();
	SceneBase* update();
	void draw();
	void destroy();

private:
	Model model_;
};

