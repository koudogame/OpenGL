#include "stdafx.h"
#include "Sphere.h"


Sphere::Sphere()
{
}

Sphere::Sphere(const glm::vec3 & CenterPoint, float Radius)
{
	center_point_ = CenterPoint;
	radius_ = Radius;
}


Sphere::~Sphere()
{
}

bool Sphere::collision(Shape * Owner)
{
	return Owner->collision(this);
}

bool Sphere::collision(AABB * Owner)
{
	return false;
}

bool Sphere::collision(OBB * Owner)
{
	return false;
}

bool Sphere::collision(Segment * Owner)
{
	return false;
}

bool Sphere::collision(Sphere * Owner)
{
	return false;
}

bool Sphere::collision(Poligon * Owner)
{
	return false;
}

void Sphere::setWorld(const glm::mat4 & World)
{
}
