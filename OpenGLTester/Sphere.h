#pragma once
#include "Shape.h"
#include "AABB.h"

class Sphere :
	public Shape
{
public:
	Sphere();
	Sphere(const glm::vec3& CenterPoint,float Radius);
	~Sphere();

public:
	//Double Dispatch
	bool collision(Shape* Owner);

	bool collision(AABB* Owner);
	bool collision(OBB* Owner);
	bool collision(Segment* Owner);
	bool collision(Sphere* Owner);
	bool collision(Poligon* Owner);

	void setWorld(const glm::mat4& World);

	inline const AABB* getBox()const { return &box_; }

	//setter getter
	inline void setCenterPoint(const glm::vec3& CenterPoint) { center_point_ = CenterPoint; }
	inline const glm::vec3& getCenterPoint()const { return center_point_; }
	inline void setRadius(float Radius) { radius_ = Radius; }
	inline const float getRadius()const { return radius_; }

private:
	AABB box_;
	glm::vec3 center_point_;
	float radius_;
};

