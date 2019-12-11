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
}
