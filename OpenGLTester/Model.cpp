#include "stdafx.h"
#include "Model.h"
#include "Shader.h"

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
	return true;
}

void Model::draw()
{
	glUseProgram(program_);

	//glUniform1i(textrue_location_, 0);

	object_->draw();
}

GLuint Model::getUniformLocation(std::string VariableName)
{
	return glGetUniformLocation(program_, VariableName.c_str());
}