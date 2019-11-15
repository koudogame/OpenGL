#pragma once
#include "Object.h"
#include "Shape.h"

class Model
{
public:
	Model();
	~Model();

public:
	bool init(std::string ModelName, std::string TextureName = "");
	void setPosition(const glm::mat4& Position);
	void draw();
	const Capsule& getOBB() { return obb_; }

private:
	std::unique_ptr<Object> object_;
	GLuint program_;

	GLuint textrue_location_;
	GLuint view_model_location_;
	GLuint projection_location_;
	GLuint nomal_location_;

	Capsule obb_;
	glm::mat4 position_;

private:
	void SendSheder();
	GLuint getUniformLocation(std::string VariableName);
};
