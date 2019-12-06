#pragma once
#include "Shape.h"
class OBB :
	public Shape
{
public:
	OBB();
	~OBB();

public:
	//Visitor
	bool collision(Shape* Owner);

	//“–‚½‚è”»’è‚ÌÀÛ‚Ìˆ—‚ğÀ‘•
	bool collision(AABB* Owner);
	bool collision(OBB* Owner);
	bool collision(Segment* Owner);
	bool collision(Sphere* Owner);
	bool collision(Plane* Owner);
	bool collision(Poligon* Owner);

	void setWorld(const glm::mat4& World);

	//setter getter
	inline void setCenter(const glm::vec3& CenterPoint) { center_point_ = CenterPoint; }
	inline const glm::vec3& getCenter() { return center_point_; }
	inline void setDirection(int Direction);
private:
	glm::vec3 center_point_;
	glm::vec3 direction_[3];
	glm::vec3 length_;
};

