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
	bool collision(const Shape*, const Shape*) { return true; };
	//�������E������
	bool OBBtoOBB(const OBB& Obj1, const OBB& Obj2);
	//�����m�̔���
	bool SpheretoSphere(const Sphere& Obj1, const Sphere& Obj2);
	//BOX���m�̔���
	bool AABBtoAABB(const AABB& Obj1, const AABB& Obj2);
	//�J�v�Z�����m�̔���
	bool CapsuletoCapsule(const Capsule& Obj1, const Capsule& Obj2);
	bool CapsuletoCapsule(const Capsule& Obj1, const Capsule& Obj2, glm::vec3& Perpendicular1, glm::vec3& Perpendicular2, float& Coefficient1, float& Coefficient2);

	//TODO:�Փ˖��m�F
	//���C�ƕ��ʂ̔���
	bool RaytoPlane(const Line& Segment,const Plane& Plane);
	//�_�ƃ|���S���̔���
	bool PointtoPoligon(glm::vec3 Point,const Poligon& Poligon);
	//�����ƕ��ʂ̌�_
	glm::vec3 intersectionLinetoPlane(const Line& Line,const Plane& Plane);
	//OBB�ƕ��ʂ̔���
	bool OBBtoPlane(const OBB& Obj1, const Plane& Plane, float* RepelAmount = nullptr);
	//OBB��AABB�̔���
	bool OBBtoAABB(const OBB& Obj1, const AABB& Obj2);

private:
	//�������E���̒��������߂�
	float lenSegOnSparateAxis(glm::vec3 *n_ae1, glm::vec3 *be1, glm::vec3 *be2, glm::vec3 *be3 = nullptr);
	//�����Ɛ����̍ŒZ����
	float lengthSegmenttoSegment(const Line& Segment1, const Line& Segment2, glm::vec3& PerpendicularBuffer1, glm::vec3& PerpendicularBuffer2, float& CoefficientBuffer1, float& CoefficientBuffer2);
	//�_��������̍ŒZ����
	float lengthPointtoLine(const glm::vec3 Point, const Line& Segment,glm::vec3& PerpendicularBuffer,float& CoefficientBuffer);
	//3�_�Ō`�������p�x���s�p���ǂ���
	//�n�_�F�Ώۊp�F�I�_
	bool sharpAngle(const glm::vec3& Point1, glm::vec3 Point2,glm::vec3 Point3);
	//�����ƕ��ʔ���
	bool LinetoPlane(const Line& Segment,const Plane& Plane);
	//2�����Ԃ̍ŒZ����
	float lengthLinetoLine(const Line& Line1,const Line& Line2, glm::vec3& PerpendicularBuffer1, glm::vec3& PerpendicularBuffer2, float& CoefficientBuffer1, float& CoefficientBuffer2);
	//�_�ƕ��ʂ̍ŒZ����
	float lengthPointtoPlane(const glm::vec3 Point,const Plane& Plane);
	//�_��OBB
	float lengthPointoOBB(const glm::vec3& Point, const OBB& Obj);
	//�_��AABB
	float lengthPointoAABB(const glm::vec3& Point, const AABB& Obj);
};

