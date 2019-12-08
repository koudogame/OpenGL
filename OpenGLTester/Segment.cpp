#include "stdafx.h"
#include "Segment.h"
#include "ShapeList.h"

Segment::Segment(const glm::vec3 Start)
{
	start_ = Start;
}

Segment::Segment(const glm::vec3 Start, const glm::vec3 & Ray)
{
	start_ = Start;
	ray_ = Ray;
}

Segment::~Segment()
{
}

bool Segment::collision(Shape * Owner)
{
	return Owner->collision(this);
}

bool Segment::collision(AABB * Owner)
{
	return false;
}

bool Segment::collision(OBB * Owner)
{
	return false;
}

bool Segment::collision(Segment * Owner)
{
	return false;
}

bool Segment::collision(Sphere * Owner)
{
	return false;
}

bool Segment::collision(Poligon * Owner)
{
	return false;
}

void Segment::setWorld(const glm::mat4 & World)
{
	start_ = World * glm::vec4(start_, 1.0F);
	createAABB();
}

inline void Segment::setStart(const glm::vec3 & Start)
{
	start_ = Start;
	createAABB();
}


inline void Segment::setRay(const glm::vec3 & Ray)
{
	ray_ = Ray;
	createAABB();
}

inline void Segment::setEnd(const glm::vec3 & End)
{
	ray_ = End - start_;
	createAABB();
}

void Segment::createAABB()
{
	glm::vec3 end = start_ + ray_;
	glm::vec3 max, min;

	max.x = std::max(start_.x, end.x);
	max.y = std::max(start_.y, end.y);
	max.z = std::max(start_.z, end.z);
	min.x = std::min(start_.x, end.x);
	min.y = std::min(start_.y, end.y);
	min.z = std::min(start_.z, end.z);

	box_.setMax(max);
	box_.setMin(min);
}
