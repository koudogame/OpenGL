#include "stdafx.h"
#include "Segment.h"
#include "ShapeList.h"

Segment::Segment(const glm::vec3 Start, const glm::vec3 & End)
{
	start_ = Start;
	end_ = End;
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
	world_ = World;
	createBox();
}

inline void Segment::setStart(const glm::vec3 & Start)
{
	start_ = Start;
}


inline void Segment::setRay(const glm::vec3 & Ray)
{
	end_ = start_ + Ray;
}

inline void Segment::setEnd(const glm::vec3 & End)
{
	end_ = End;
}

const glm::vec3 Segment::getStart() const
{
	return world_ * glm::vec4(start_, 1.0F);
}

const glm::vec3 Segment::getRay() const
{
	return getEnd() - getStart();
}

glm::vec3 Segment::getEnd() const
{
	return world_ * glm::vec4(end_, 1.0F);
}

void Segment::createBox()
{
	glm::vec3 max, min;

	max.x = std::max(getStart().x, getEnd().x);
	max.y = std::max(getStart().y, getEnd().y);
	max.z = std::max(getStart().z, getEnd().z);
	min.x = std::min(getStart().x, getEnd().x);
	min.y = std::min(getStart().y, getEnd().y);
	min.z = std::min(getStart().z, getEnd().z);

	box_.setMax(max);
	box_.setMin(min);
}
