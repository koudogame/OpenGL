#pragma once
#include "Shape.h"
#include "AABB.h"

class Segment :
	public Shape
{
	//****線分の設定は必ず始点から行うこと****
public:
	Segment() = default;
	Segment(const glm::vec3 Start);
	Segment(const glm::vec3 Start, const glm::vec3& Ray);
	~Segment();

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
	inline void setStart(const glm::vec3& Start);
	inline glm::vec3& getStart() {return start_};
	inline void setRay(const glm::vec3& Ray);
	inline const glm::vec3& getRay() { return ray_; };
	inline void setEnd(const glm::vec3& End);
	inline glm::vec3 getEnd() { return start_ + ray_; };

private:
	AABB box_;
	glm::vec3 start_;
	glm::vec3 ray_;

private:
	void createAABB();
};

