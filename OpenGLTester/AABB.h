#pragma once
#include "Shape.h"
class AABB :
	public Shape
{
public:
	AABB() = default;
	AABB(const glm::vec3& Max,const glm::vec3& Min);
	~AABB();

public:
	//Visitor
	bool collision(Shape* Owner);

	bool collision(AABB* Owner);
	bool collision(OBB* Owner);
	bool collision(Segment* Owner);
	bool collision(Sphere* Owner);
	bool collision(Plane* Owner);
	bool collision(Poligon* Owner);

	void setWorld(const glm::mat4& World);

	//getter setter
	inline void setMin(const glm::vec3& Min) { min_ = Min; }
	inline const glm::vec3& getMin() { return min_; }
	inline void setMax(const glm::vec3& Min) { min_ = Min; }
	inline const glm::vec3& getMax() { return min_; }

private:
	glm::vec3 min_;
	glm::vec3 max_;
};

