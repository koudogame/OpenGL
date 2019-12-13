#pragma once
#include "Object.h"
#include "Shape.h"
#include "ObjectManager.h"

class Model
{
public:
	Model();
	virtual ~Model();

	//---プログラマ要実装関数---
public:
	//当たり判定前の処理( 移動など )
	virtual void firstUpdate() {}
	//当たり判定後の処理( 補正など )
	virtual void lastUpdate() {}
	//破棄
	virtual void destroy() { ObjectManager::get()->release(object_); };

protected:
	//初期化
	virtual bool init() { return true; }

	//---------------------------

	//--要内部利用関数---
protected:
	bool readModel(std::string ModelName, std::string TextureName = "");
	inline void setUseCamName(std::string CameraName) { camera_name_ = CameraName; }
	inline void death() { alive_ = false; }
protected:
	std::vector<Shape*> shape_;
	glm::mat4 world_;

	//-------------------


public:
	void Initialization();
	virtual void draw()final;
	const std::vector<Shape*>& getShape() { return shape_; }
	void moveShape();
	bool isAlive() { return alive_; }

private:
	Object* object_;
	GLuint program_;
	std::string camera_name_;
	bool alive_;

	//Shederへ渡すためのロケーター
	GLuint textrue_location_;
	GLuint view_model_location_;
	GLuint projection_location_;
	GLuint nomal_location_;

private:
	void SendSheder();
	GLuint getUniformLocation(std::string VariableName);

protected:
	virtual void update() = delete;
};