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

	void setWorld(const glm::mat4& World);

	inline const AABB* getBox()const { return &box_; }

	//setter getter
	inline const std::tuple<glm::vec3, glm::vec3, glm::vec3>getPoint()const { return std::make_tuple(point_[0], point_[1], point_[2]); }
	inline const glm::vec3& getPoint(int PointNum)const { return PointNum < 3 ? point_[PointNum] : glm::vec3(0.0F); }
	inline void setPoint(int PointNum, const glm::vec3& Point) { if (PointNum < 3)point_[PointNum] = Point; }
	inline void setPoint(const glm::vec3& Point1, const glm::vec3& Point2, const glm::vec3& Point3) { point_[0] = Point1; point_[1] = Point2; point_[2] = Point3; }
	inline const glm::vec3& getNomal()const { return nomal_; }
	inline void setNomal(const glm::vec3& Nomal) { nomal_ = Nomal; }
private:
	AABB box_;
	glm::vec3 point_[3];
	glm::vec3 nomal_;
};

