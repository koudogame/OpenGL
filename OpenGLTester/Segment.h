#pragma once
#include "Shape.h"
#include "AABB.h"

class Segment :
	public Shape
{
public:
	Segment() = default;
	Segment(const glm::vec3 Start, const glm::vec3& End);
	~Segment();

public:
	//Double Dispatch
	bool collision(Shape* Owner);

	bool collision(AABB* Owner);
	bool collision(OBB* Owner);
	bool collision(Segment* Owner);
	bool collision(Sphere* Owner);
	bool collision(Poligon* Owner);

	inline const AABB* getBox()const { return &box_; }
	void setWorld(const glm::mat4& World);

	//getter setter
	inline void setStart(const glm::vec3& Start);
	inline void setRay(const glm::vec3& Ray);
	inline void setEnd(const glm::vec3& End);
	const glm::vec3 getStart()const;
	const glm::vec3 getRay()const;
	glm::vec3 getEnd()const;

private:
	AABB box_;
	glm::vec3 start_;
	glm::vec3 end_;

private:
	void createBox();
};

