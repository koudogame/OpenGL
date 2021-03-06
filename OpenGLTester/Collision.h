#pragma once
#include "Model.h"
#include "ShapeList.h"

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
	//分離境界軸判定
	bool OBBtoOBB(const OBB& Obj1, const OBB& Obj2);
	//球同士の判定
	bool SpheretoSphere(const Sphere& Obj1, const Sphere& Obj2);
	//BOX同士の判定
	bool AABBtoAABB(const AABB& Obj1, const AABB& Obj2);
	////カプセル同士の判定
	//bool CapsuletoCapsule(const Capsule& Obj1, const Capsule& Obj2);
	//bool CapsuletoCapsule(const Capsule& Obj1, const Capsule& Obj2, glm::vec3& Perpendicular1, glm::vec3& Perpendicular2, float& Coefficient1, float& Coefficient2);

	//TODO:衝突未確認
	//レイと平面の判定
	bool RaytoPlane(const Segment& Segment,const glm::vec3& Point,const glm::vec3& Nomal);
	//点とポリゴンの判定
	bool PointtoPoligon(glm::vec3 Point,const Poligon& Poligon);
	//直線と平面の交点
	glm::vec3 intersectionLinetoPlane(const Segment& Line, const glm::vec3& Point, const glm::vec3& Nomal);
	//OBBと平面の判定
	bool OBBtoPlane(const OBB& Obj1, const glm::vec3& Point, const glm::vec3& Nomal, float* RepelAmount = nullptr);
	//OBBとAABBの判定
	bool OBBtoAABB(const OBB& Obj1, const AABB& Obj2);

private:
	//分離境界線の長さを求める
	float lenSegOnSparateAxis(glm::vec3 *n_ae1, glm::vec3 *be1, glm::vec3 *be2, glm::vec3 *be3 = nullptr);
	//線分と線分の最短距離
	float lengthSegmenttoSegment(const Segment& Segment1, const Segment& Segment2, glm::vec3& PerpendicularBuffer1, glm::vec3& PerpendicularBuffer2, float& CoefficientBuffer1, float& CoefficientBuffer2);
	//点から線分の最短距離
	float lengthPointtoLine(const glm::vec3 Point, const Segment& Segment,glm::vec3& PerpendicularBuffer,float& CoefficientBuffer);
	//3点で形成される角度が鋭角かどうか
	//始点：対象角：終点
	bool sharpAngle(const glm::vec3& Point1, glm::vec3 Point2,glm::vec3 Point3);
	//線分と平面判定
	bool LinetoPlane(const Segment& Segment, const glm::vec3& Point, const glm::vec3& Nomal);
	//2直線間の最短距離
	float lengthLinetoLine(const Segment& Line1,const Segment& Line2, glm::vec3& PerpendicularBuffer1, glm::vec3& PerpendicularBuffer2, float& CoefficientBuffer1, float& CoefficientBuffer2);
	//点と平面の最短距離
	float lengthPointtoPlane(const glm::vec3 Point, const glm::vec3& PlanePoint, const glm::vec3& Nomal);
	//点とOBB
	float lengthPointoOBB(const glm::vec3& Point, const OBB& Obj);
	//点とAABB
	float lengthPointoAABB(const glm::vec3& Point, const AABB& Obj);
};

