#include "stdafx.h"
#include "AABB.h"
#include "ShapeList.h"


AABB::AABB(const glm::vec3 & Max, const glm::vec3 & Min)
{
	max_ = Max;
	min_ = Min;
}

AABB::~AABB()
{
}

bool AABB::collision(Shape * Owner)
{
	return Owner->collision(this);
}

bool AABB::collision(AABB * Owner)
{
	return false;
}

bool AABB::collision(OBB * Owner)
{
	return false;
}

bool AABB::collision(Segment * Owner)
{
	return false;
}

bool AABB::collision(Sphere * Owner)
{
	return false;
}

bool AABB::collision(Plane * Owner)
{
	return false;
}

bool AABB::collision(Poligon * Owner)
{
	return false;
}

void AABB::setWorld(const glm::mat4 & World)
{
	min_ = World * glm::vec4(min_, 1.0F);
	max_ = World * glm::vec4(max_, 1.0F);
}
