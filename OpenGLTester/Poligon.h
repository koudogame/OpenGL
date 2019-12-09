#pragma once
#include "Shape.h"
#include "AABB.h"

class Poligon :
	public Shape
{
public:
	Poligon();
	Poligon(const glm::vec3& Point1, const glm::vec3& Point2, const glm::vec3& Point3, const glm::vec3& Nomal);
	~Poligon();

public:
	//Double Dispatch
	bool collision(Shape* Owner);

	bool collision(AABB* Owner);
	bool collision(OBB* Owner);
	bool collision(Segment* Owner);
	bool collision(Sphere* Owner);
	bool collision(Poligon* Owner);

	inline const AABB* getBox()const { return &box_; }

	//setter
	inline void setPoint(int PointNum, const glm::vec3& Point) { if (PointNum < 3)point_[PointNum] = Point; }
	inline void setPoint(const glm::vec3& Point1, const glm::vec3& Point2, const glm::vec3& Point3) { point_[0] = Point1; point_[1] = Point2; point_[2] = Point3; }
	inline void setNomal(const glm::vec3& Nomal) { nomal_ = Nomal; }
	//getter
	const std::tuple<glm::vec3, glm::vec3, glm::vec3>getPoint()const;
	const glm::vec3 getPoint(int PointNum)const;
	const glm::vec3 getNomal()const;
private:
	AABB box_;
	glm::vec3 point_[3];
	glm::vec3 nomal_;
};

