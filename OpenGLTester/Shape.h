#pragma once

//TODO:���ꂼ��̌`���N���X����
//		���ꂼ�ꂪCollision�����A�Փ˔�����s��
struct Shape
{
	virtual ~Shape() = default;
};

struct AABB :public Shape
{
	glm::vec3 min;
	glm::vec3 max;
	AABB() = default;
	AABB(const glm::vec3& Max, const glm::vec3& Min)
	{
		max = Max;
		min = Min;
	}
};

struct Complex :public Shape
{
	AABB box;
};

struct Line:public Complex
{
	glm::vec3 start;
	glm::vec3 end;

	glm::vec3 getDirection()const
	{
		return end - start;
	}
};

struct OBB : public Complex
{
	glm::vec3 c_gravity = glm::vec3(0.0);//�s��̍��W����

	glm::vec3 direction[3] = {};	//�e�I�u�W�F�N�g������world�s��̉�]����
	glm::vec3 length = glm::vec3(0.0);
};

struct Sphere :public Complex
{
	glm::vec3 c_gravity;
	float radius;
};

struct Capsule : public Complex
{
	Line line;
	float radius;
};

struct Plane :public Complex
{
	glm::vec3 c_ground;
	glm::vec3 nomal;
};

struct Poligon :public Plane
{
	glm::vec3 point[3];
};
