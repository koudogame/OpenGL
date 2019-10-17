#include "stdafx.h"
#include "Model.h"
#include "Shader.h"
#include "Camera.h"

Model::Model()
{
}

Model::~Model()
{
}



bool Model::init()
{
	program_ = Shader::Get()->loadProgram("point.vert", "point.frag");
	if (program_ == 0)
		return false;
	object_ = std::make_unique<Object>();
	if (object_.get() == nullptr || !object_->createVertexData("Dice.obj"))
		return false;
	object_->loadTexture("Dice.png");
	textrue_location_ = getUniformLocation("tex");
	view_location_ = getUniformLocation("view");
	projection_location_ = getUniformLocation("projection");
	position_location_ = getUniformLocation("position");

	if (textrue_location_ < 0 ||
		view_location_ < 0 ||
		projection_location_ < 0 ||
		position_location_ < 0)
		return false;

	position_ = glm::mat4(1.0F);

	return true;
}

void Model::updata()
{
	static float angle = 0;
	glm::mat4 position;
	position = glm::rotate(glm::radians(++angle), glm::vec3(1.0F, 0.0F, 1.0F));


	glUseProgram(program_);

	//Vertex Shader Uniform
	glUniformMatrix4fv(view_location_, 1, GL_FALSE, &Camera::Get()->getView()[0][0]);
	glUniformMatrix4fv(projection_location_, 1, GL_FALSE, &Camera::Get()->getProjection()[0][0]);
	glUniformMatrix4fv(position_location_, 1, GL_FALSE, &position[0][0]);
}

void Model::draw()
{

	glUseProgram(program_);
	//Fragment Shader Uniform
	glUniform1i(textrue_location_, 0);

	object_->draw();
}

GLuint Model::getUniformLocation(std::string VariableName)
{
	return glGetUniformLocation(program_, VariableName.c_str());
}