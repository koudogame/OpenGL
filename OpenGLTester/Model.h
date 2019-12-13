#pragma once
#include "Object.h"
#include "Shape.h"
#include "ObjectManager.h"

class Model
{
public:
	Model();
	virtual ~Model();

	//---�v���O���}�v�����֐�---
public:
	//�����蔻��O�̏���( �ړ��Ȃ� )
	virtual void firstUpdate() {}
	//�����蔻���̏���( �␳�Ȃ� )
	virtual void lastUpdate() {}
	//�j��
	virtual void destroy() { ObjectManager::get()->release(object_); };

protected:
	//������
	virtual bool init() { return true; }

	//---------------------------

	//--�v�������p�֐�---
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

	//Sheder�֓n�����߂̃��P�[�^�[
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