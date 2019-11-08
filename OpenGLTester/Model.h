#pragma once
#include "Object.h"

struct OBB
{
	glm::vec3 position = glm::vec3(0.0);//�s��̍��W����

	glm::vec3 direction[3] = {};	//�e�I�u�W�F�N�g������world�s��̉�]����
	glm::vec3 length = glm::vec3(0.0);
};

class Model
{
public:
	Model();
	~Model();

public:
	bool init(std::string ModelName, std::string TextureName = "");
	void setPosition(const glm::mat4& Position);
	void draw();

private:
	std::unique_ptr<Object> object_;
	GLuint program_;

	GLuint textrue_location_;
	GLuint view_model_location_;
	GLuint projection_location_;
	GLuint nomal_location_;

	OBB obb_;
	glm::mat4 position_;

private:
	void SendSheder();
	GLuint getUniformLocation(std::string VariableName);
};
