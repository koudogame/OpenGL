#pragma once
#include "Shape.h"
#include "AABB.h"

class Segment :
	public Shape
{
	//****�����̐ݒ�͕K���n�_����s������****
public:
	Segment() = default;
	Segment(const glm::vec3 Start);
	Segment(const glm::vec3 Start, const glm::vec3& Ray);
	~Segment();

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

	//getter setter
	inline void setStart(const glm::vec3& Start);
	inline const glm::vec3& getStart()const { return start_; };
	inline void setRay(const glm::vec3& Ray);
	inline const glm::vec3& getRay()const { return ray_; };
	inline void setEnd(const glm::vec3& End);
	inline glm::vec3 getEnd()const { return start_ + ray_; };

private:
	AABB box_;
	glm::vec3 start_;
	glm::vec3 ray_;

private:
	void createAABB();
};

