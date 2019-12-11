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

	inline const AABB* getBox()const { return &box_; }
	void setWorld(const glm::mat4& World);

	//setter getter
	inline void setLocal(const glm::mat4& Local) { local_ = Local; }
	inline void setLength(const glm::vec3& Length) { length_ = Length; }
	inline const glm::vec3& getLength()const { return length_; }
	const glm::vec3 getCenter()const;
	const glm::vec3 getDirection(int DirectionID)const;
private:
	AABB box_;
	glm::mat4 local_;
	glm::vec3 length_;

private:
	void createBox();
};

