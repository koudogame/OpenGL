#pragma once
#include "Object.h"
#include "Shape.h"

class Model
{
public:
	Model();
	~Model();

	//---�v���O���}�v�����֐�---
public:
	//�����蔻��O�̏���( �ړ��Ȃ� )
	virtual void firstUpdate() {}
	//�����蔻���̏���( �␳�Ȃ� )
	virtual void lastUpdate() {}

	//---------------------------

	//--�v�������p�֐�---
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

	//Sheder�֓n�����߂̃��P�[�^�[
	GLuint textrue_location_;
	GLuint view_model_location_;
	GLuint projection_location_;
	GLuint nomal_location_;

private:
	void SendSheder();
	GLuint getUniformLocation(std::string VariableName);
};
