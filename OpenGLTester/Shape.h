#pragma once

class AABB;
class OBB;
class Segment;
class Sphere;
class Poligon;

class Shape
{
public:
	virtual ~Shape() = default;

public:
	//Double Dispatch
	virtual bool collision(Shape* Owner) = 0;

	//当たり判定の実際の処理を実装
	virtual bool collision(AABB* Owner) = 0;
	virtual bool collision(OBB* Owner) = 0;
	virtual bool collision(Segment* Owner) = 0;
	virtual bool collision(Sphere* Owner) = 0;
	virtual bool collision(Poligon* Owner) = 0;

	virtual inline void setWorld(const glm::mat4& World) { world_ = World; }

	virtual const AABB* getBox()const = 0;

	//デバッグ用
	virtual void draw() {}

protected:
	glm::mat4 world_;
};