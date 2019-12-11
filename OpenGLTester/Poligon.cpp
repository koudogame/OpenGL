#include "stdafx.h"
#include "Poligon.h"
#include "Collision.h"


Poligon::Poligon()
{
}

Poligon::Poligon(const glm::vec3 & Point1, const glm::vec3 & Point2, const glm::vec3 & Point3)
{
	point_[0] = Point1;
	point_[0] = Point2;
	point_[3] = Point3;
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

void Poligon::setWorld(const glm::mat4 & World)
{
	world_ = World;
	createBox();
}

const std::tuple<glm::vec3, glm::vec3, glm::vec3> Poligon::getPoint() const
{
	return std::make_tuple(world_ * glm::vec4(point_[0], 1.0F),
		world_ * glm::vec4(point_[1], 1.0F),
		world_ * glm::vec4(point_[2], 1.0F));
}

const glm::vec3 Poligon::getPoint(int PointNum) const
{
	return world_ * glm::vec4(point_[PointNum], 1.0F);
}

const glm::vec3 Poligon::getNomal() const
{
	glm::vec3 point[3];
	for (int i = 0; i < 3; ++i)
		point[i] = world_ * glm::vec4(point_[i], 1.0F);

	//基点からのベクトルを算出
	glm::vec3 vec[2] = { point[1] - point[0],point[2] - point[0] };

	//外積を用いて正規化された法線を求める
	return glm::normalize(glm::cross(vec[0], vec[1]));
}

void Poligon::createBox()
{
	glm::vec3 max, min;

	max.x = std::max(std::max(point_[0].x, point_[1].x), point_[2].x);
	max.y = std::max(std::max(point_[0].y, point_[1].y), point_[2].y);
	max.z = std::max(std::max(point_[0].z, point_[1].z), point_[2].z);
	min.x = std::min(std::min(point_[0].x, point_[1].x), point_[2].x);
	min.y = std::min(std::min(point_[0].y, point_[1].y), point_[2].y);
	min.z = std::min(std::min(point_[0].z, point_[1].z), point_[2].z);
	box_.setMax(max);
	box_.setMin(min);
}
