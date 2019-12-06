#include "stdafx.h"
#include "Model.h"
#include "Shader.h"
#include "CameraManager.h"
#include "TaskManger.h"
#include "Space.h"

Model::Model()
{
	TaskManager::get()->regist(this);
}

Model::~Model()
{
	TaskManager::get()->unregist(this);
}


bool Model::readModel(std::string ModelName, std::string TextureName)
{
	program_ = Shader::Get()->loadProgram("point.vert", "point.frag");
	if (program_ == 0)
		return false;
	object_ = std::make_unique<Object>();
	if (object_.get() == nullptr || !object_->createVertexData(ModelName))
		return false;
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
void Model::SendSheder()
{
	auto camera = CameraManager::get()->getCamera("main");
	if (camera == nullptr)
		return;
	glUseProgram(program_);
	glm::mat4 view_model = camera->getView() * world_;
	//–@ü‚ðC³‚·‚é‚½‚ß‚Ì‹t“]’us—ñ‚Ìì¬
	glm::mat3 nomal_matrix = glm::transpose(glm::inverse(view_model));
	//Vertex Shader Uniform
	glUniformMatrix4fv(view_model_location_, 1, GL_FALSE, &view_model[0][0]);
	glUniformMatrix4fv(projection_location_, 1, GL_FALSE, &camera->getProjection()[0][0]);
	glUniformMatrix3fv(nomal_location_, 1, GL_FALSE, &nomal_matrix[0][0]);
}

void Model::draw()
{
	SendSheder();
	glUseProgram(program_);
	//Fragment Shader Uniform
	glUniform1i(textrue_location_, 0);

	object_->draw();
}

void Model::moveShape()
{
	for (auto& itr : shape_)
		itr.setWorld(world_);

	Space::get()->regist(this);
}

GLuint Model::getUniformLocation(std::string VariableName)
{
	return glGetUniformLocation(program_, VariableName.c_str());
}