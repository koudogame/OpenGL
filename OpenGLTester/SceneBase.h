#pragma once
class SceneBase
{
public:
	SceneBase() = default;
	virtual ~SceneBase() = default;

public:
	virtual bool init() = 0;
	virtual SceneBase* update() = 0;
	virtual void draw() = 0;
	virtual void destroy() = 0;
};

