#include "stdafx.h"
#include "Poligon.h"


Poligon::Poligon()
{
}

Poligon::Poligon(const glm::vec3 & Point1, const glm::vec3 & Point2, const glm::vec3 & Point3, const glm::vec3 & Nomal)
{
	point_[0] = Point1;
	point_[0] = Point2;
	point_[3] = Point3;
	nomal_ = Nomal;
}


Poligon::~Poligon()
{
}

bool Poligon::collision(Shape * Owner)
{
	return Owner->collision(this);
}

bool Poligon::collision(AABB * Owner)
{
	return false;
}

bool Poligon::collision(OBB * Owner)
{
	return false;
}

bool Poligon::collision(Segment * Owner)
{
	return false;
}

bool Poligon::collision(Sphere * Owner)
{
	return false;
}

bool Poligon::collision(Poligon * Owner)
{
	return false;
}

const std::tuple<glm::vec3, glm::vec3, glm::vec3> Poligon::getPoint() const
{
	return std::tuple<glm::vec3, glm::vec3, glm::vec3>();
}

const glm::vec3 Poligon::getPoint(int PointNum) const
{
	return glm::vec3();
}

const glm::vec3 Poligon::getNomal() const
{
	return glm::vec3();
}
