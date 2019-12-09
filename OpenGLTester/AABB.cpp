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

bool AABB::collision(Poligon * Owner)
{
	return false;
}

const glm::vec3 AABB::getMin() const
{
	return glm::vec3();
}

const glm::vec3 AABB::getMax() const
{
	return glm::vec3();
}
