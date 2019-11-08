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



bool Model::init(std::string ModelName, std::string TextureName)
{
	program_ = Shader::Get()->loadProgram("point.vert", "point.frag");
	if (program_ == 0)
		return false;
	object_ = std::make_unique<Object>();
	if (object_.get() == nullptr || !object_->createVertexData(ModelName))
		return false;
	obb_.length = object_.get()->getMaxLength();
	if (TextureName != "")
		object_->loadTexture(TextureName);
	textrue_location_ = getUniformLocation("tex");
	view_model_location_ = getUniformLocation("model_view");
	projection_location_ = getUniformLocation("projection");
	nomal_location_ = getUniformLocation("nomal_matrix");

	if (textrue_location_ < 0 ||
		view_model_location_ < 0 ||
		projection_location_ < 0 ||
		nomal_location_ < 0)
		return false;

	return true;
}

void Model::setPosition(const glm::mat4 & Position)
{
	position_ = Position;
	for (int i = 0; i < 3; ++i)
		obb_.direction[i] = glm::transpose(Position)[i];
}

void Model::SendSheder()
{
	glUseProgram(program_);
	glm::mat4 view_model = Camera::Get()->getView() * position_;
	//–@ü‚ðC³‚·‚é‚½‚ß‚Ì‹t“]’us—ñ‚Ìì¬
	glm::mat3 nomal_matrix = glm::transpose(glm::inverse(view_model));
	//Vertex Shader Uniform
	glUniformMatrix4fv(view_model_location_, 1, GL_FALSE, &view_model[0][0]);
	glUniformMatrix4fv(projection_location_, 1, GL_FALSE, &Camera::Get()->getProjection()[0][0]);
	glUniformMatrix3fv(nomal_location_, 1, GL_FALSE, &nomal_matrix[0][0]);
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