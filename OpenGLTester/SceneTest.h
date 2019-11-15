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
	void setCamPosition();
	SceneBase* update();
	void camControl(GLFWgamepadstate &state);
	void draw();
	void destroy();

private:
	Model model_;
	Model target_;

	float length_;

	glm::vec3 position_;
	glm::vec3 cam_position_;
	glm::vec2 rotate_;
};

