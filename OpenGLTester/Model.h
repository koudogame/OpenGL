#pragma once
#include "Object.h"
#include "Shape.h"

class Model
{
public:
	Model();
	~Model();

	//---プログラマ要実装関数---
public:
	//当たり判定前の処理( 移動など )
	virtual void firstUpdate() {}
	//当たり判定後の処理( 補正など )
	virtual void lastUpdate() {}

	//---------------------------

	//--要内部利用関数---
protected:
	bool readModel(std::string ModelName, std::string TextureName = "");
protected:
	std::vector<Shape> shape_;
	glm::mat4 world_;

	//-------------------


public:
	void draw();
	const std::vector<Shape>& getShape() { return shape_; }

private:
	std::unique_ptr<Object> object_;
	GLuint program_;

	//Shederへ渡すためのロケーター
	GLuint textrue_location_;
	GLuint view_model_location_;
	GLuint projection_location_;
	GLuint nomal_location_;

private:
	void SendSheder();
	GLuint getUniformLocation(std::string VariableName);
};
