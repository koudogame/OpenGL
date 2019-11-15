#pragma once

//TODO:���ꂼ��̌`���N���X����
//		���ꂼ�ꂪCollision�����A�Փ˔�����s��
struct Shape
{
};

struct Line
{
	glm::vec3 start;
	glm::vec3 end;
};

struct OBB : public Shape
{
	glm::vec3 c_gravity = glm::vec3(0.0);//�s��̍��W����

	glm::vec3 direction[3] = {};	//�e�I�u�W�F�N�g������world�s��̉�]����
	glm::vec3 length = glm::vec3(0.0);
};

struct Sphere :public Shape
{
	glm::vec3 c_gravity;
	float radius;
};

struct Capsule : public Shape
{
	Line line;
	float radius;
};

struct AABB :public Shape
{
	glm::vec3 min;
	glm::vec3 max;
};

struct Plane :public Shape
{
	glm::vec3 c_ground;
	glm::vec3 nomal;
};
