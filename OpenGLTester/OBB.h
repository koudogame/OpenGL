#pragma once
#include "Shape.h"
#include "AABB.h"

class OBB :
	public Shape
{
public:
	OBB();
	~OBB();

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
	inline void setCenter(const glm::vec3& CenterPoint) { center_point_ = CenterPoint; }
	inline const glm::vec3& getCenter()const { return center_point_; }

private:
	AABB box_;
	glm::vec3 center_point_;
	glm::vec3 direction_[3];
	glm::vec3 length_;
};
