#pragma once

//TODO:それぞれの形をクラス分け
//		それぞれがCollisionを内包し、衝突判定を行う
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
	glm::vec3 c_gravity = glm::vec3(0.0);//行列の座標成分

	glm::vec3 direction[3] = {};	//各オブジェクトが持つworld行列の回転成分
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
