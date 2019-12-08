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

	//“–‚½‚è”»’è‚ÌÀÛ‚Ìˆ—‚ğÀ‘•
	virtual bool collision(AABB* Owner) = 0;
	virtual bool collision(OBB* Owner) = 0;
	virtual bool collision(Segment* Owner) = 0;
	virtual bool collision(Sphere* Owner) = 0;
	virtual bool collision(Poligon* Owner) = 0;

	virtual void setWorld(const glm::mat4& World) = 0;

	virtual const AABB* getBox()const = 0;
};