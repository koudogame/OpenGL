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
	glm::vec3 rotate_;
	float rotate_angle_;
	glm::vec3 position_;
	GLFWgamepadstate old_state_;
};

