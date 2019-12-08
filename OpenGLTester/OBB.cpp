#include "stdafx.h"
#include "OBB.h"
#include "ShapeList.h"


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
	return false;
}

bool OBB::collision(OBB * Owner)
{
	return false;
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
}
