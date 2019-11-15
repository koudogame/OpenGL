#pragma once
#include "Model.h"
class Collision
{
private:
	Collision();
	Collision(const Collision&) = delete;
	Collision operator=(const Collision&) = delete;
public:
	static Collision* get() { static Collision instance; return &instance; }
	~Collision();


public:



public:
	bool OBBtoOBB(const OBB& Obj1, const OBB& Obj2);
	bool SpheretoSphere(const Sphere& Obj1, const Sphere& Obj2);
	bool AABBtoAABB(const AABB& Obj1, const AABB& Obj2);
	bool CapsuletoCapsule(const Capsule& Obj1, const Capsule& Obj2);
	bool CapsuletoCapsule(const Capsule& Obj1, const Capsule& Obj2, glm::vec3& Perpendicular1, glm::vec3& Perpendicular2, float& Coefficient1, float& Coefficient2);
	bool RaytoPlane(const Line& Segment, const glm::vec3& Nomal, const glm::vec3& NomalPoint);

private:
	//•ª—£‹«ŠEü‚Ì’·‚³‚ğ‹‚ß‚é
	float lenSegOnSparateAxis(glm::vec3 *n_ae1, glm::vec3 *be1, glm::vec3 *be2, glm::vec3 *be3 = 0);
	//ü•ª‚Æü•ª‚ÌÅ’Z‹——£
	float lengthSegmenttoSegment(const Line& Segment1, const Line& Segment2, glm::vec3& PerpendicularBuffer1, glm::vec3& PerpendicularBuffer2, float& CoefficientBuffer1, float& CoefficientBuffer2);
	//“_‚©‚çü•ª‚ÌÅ’Z‹——£
	float lengthPointtoLine(const glm::vec3 Point, const Line& Segment,glm::vec3& PerpendicularBuffer,float& CoefficientBuffer);
	//3“_‚ÅŒ`¬‚³‚ê‚éŠp“x‚ª‰sŠp‚©‚Ç‚¤‚©
	//n“_F‘ÎÛŠpFI“_
	bool sharpAngle(const glm::vec3& Point1, glm::vec3 Point2,glm::vec3 Point3);
	//ü•ª‚Æ•½–Ê”»’è
	bool LinetoPlane(const Line& Segment, glm::vec3 PlanePoint, glm::vec3 Nomal);
	//2’¼üŠÔ‚ÌÅ’Z‹——£
	float lengthLinetoLine(const Line& Line1,const Line& Line2, glm::vec3& PerpendicularBuffer1, glm::vec3& PerpendicularBuffer2, float& CoefficientBuffer1, float& CoefficientBuffer2);
	//“_‚Æ•½–Ê‚ÌÅ’Z‹——£
	float lengthPointtoPlane(const glm::vec3 Point, glm::vec3 Nomal, glm::vec3 NomalPoint);
};

