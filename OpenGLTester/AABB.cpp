#include "stdafx.h"
#include "AABB.h"
#include "ShapeList.h"
#include "Collision.h"


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
	return Collision::get()->AABBtoAABB(*this, *Owner);
}

bool AABB::collision(OBB * Owner)
{
	return Collision::get()->OBBtoAABB(*Owner, *this);
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
	return world_ * glm::vec4(min_, 1.0F);
}

const glm::vec3 AABB::getMax() const
{
	return world_ * glm::vec4(max_, 1.0F);
}
