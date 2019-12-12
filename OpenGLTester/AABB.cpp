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

void AABB::draw()
{
	glm::vec3 vertex_point[8];
	for (auto& itr : vertex_point)
		itr = max_;

	vertex_point[1].x = min_.x;
	vertex_point[2].x = min_.x;
	vertex_point[2].z = min_.z;
	vertex_point[3].z = min_.z;
	vertex_point[4].y = min_.y;
	vertex_point[5].y = min_.y;
	vertex_point[5].x = min_.x;
	vertex_point[7].y = min_.y;
	vertex_point[7].z = min_.y;

	glBegin(GL_LINE_LOOP);
	for (auto& itr : vertex_point)
		glVertex3f(itr.x, itr.y, itr.z);
	glEnd();
}

const glm::vec3 AABB::getMin() const
{
	return world_ * glm::vec4(min_, 1.0F);
}

const glm::vec3 AABB::getMax() const
{
	return world_ * glm::vec4(max_, 1.0F);
}
