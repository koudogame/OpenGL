#include "stdafx.h"
#include "Camera.h"


Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::setView(const glm::vec3 & Eye, const glm::vec3 & Target, glm::vec3 Up)
{
	eye_ = Eye;
	target_ = Target;
	up_ = Up;
	view_ = glm::lookAt(Eye, Target, Up);
}

void Camera::setProjection(float ViewRadian, float Aspect, float Near, float Far)
{
	projection_ = glm::perspective(ViewRadian, Aspect, Near, Far);
}

void Camera::editViewEye(const glm::vec3 & Eye)
{
	setView(Eye, target_, up_);
}

void Camera::editViewTarget(const glm::vec3 & Target)
{
	setView(eye_, Target, up_);
}

void Camera::editViewUp(const glm::vec3 & Up)
{
	setView(eye_, target_, Up);
}
