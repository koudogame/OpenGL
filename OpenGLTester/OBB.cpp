#include "stdafx.h"
#include "OBB.h"
#include "ShapeList.h"
#include "Collision.h"


OBB::OBB()
{
}


OBB::~OBB()
{
}

bool OBB::collision(Shape * Owner)
{
	return Owner->collision(this);
}

bool OBB::collision(AABB * Owner)
{
	return Collision::get()->OBBtoAABB(*this,*Owner);
}

bool OBB::collision(OBB * Owner)
{
	return Collision::get()->OBBtoOBB(*this, *Owner);
}

bool OBB::collision(Segment * Owner)
{
	return false;
}

bool OBB::collision(Sphere * Owner)
{
	return false;
}

bool OBB::collision(Poligon * Owner)
{
	return false;
}

void OBB::setWorld(const glm::mat4 & World)
{
	world_ = World;
	createBox();
}

const glm::vec3 OBB::getCenter()const
{
	return (world_ * local_)[3];
}

const glm::vec3 OBB::getDirection(int DirectionID)const
{
	return (world_ * local_)[DirectionID];
}

void OBB::createBox()
{
	glm::vec3 box_point[8];
	glm::vec3 center = getCenter();
	glm::vec3 direction[3];
	for (int i = 0; i < 3; ++i)
		direction[i] = getDirection(i) * length_[i];
	box_point[0] = center + direction[0] + direction[1] + direction[2];
	box_point[1] = box_point[0] - direction[2] * 2.0F;
	box_point[2] = box_point[1] - direction[0] * 2.0F;
	box_point[3] = box_point[0] - direction[0] * 2.0F;

	box_point[4] = box_point[0] - direction[1] * 2.0F;
	box_point[5] = box_point[1] - direction[1] * 2.0F;
	box_point[6] = box_point[2] - direction[1] * 2.0F;
	box_point[7] = box_point[3] - direction[1] * 2.0F;

	glm::vec3 max = box_point[0];
	glm::vec3 min = box_point[0];

	for (auto& itr : box_point)
	{
		max.x = std::max(max.x, itr.x);
		max.y = std::max(max.y, itr.y);
		max.z = std::max(max.z, itr.z);

		min.x = std::min(min.x, itr.x);
		min.y = std::min(min.y, itr.y);
		min.z = std::min(min.z, itr.z);
	}

	box_.setMax(max);
	box_.setMin(min);
}
