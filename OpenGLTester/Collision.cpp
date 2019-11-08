#include "stdafx.h"
#include "Collision.h"


Collision::Collision()
{
}


Collision::~Collision()
{
}

bool Collision::OBBtoOBB(const OBB & Obj1, const OBB & Obj2)
{
	//OBBの中心間のベクトル
	glm::vec3 interval = Obj1.position - Obj2.position;

	//各方向ベクトル
	//[nomal,denomal][a,b][x,y,z]
	glm::vec3 direction_vector[2][2][3];
	//Obj1
	direction_vector[0][0][0] = Obj1.direction[0], direction_vector[1][0][0] = Obj1.direction[0] * Obj1.length.x;
	direction_vector[0][0][1] = Obj1.direction[1], direction_vector[1][0][1] = Obj1.direction[1] * Obj1.length.y;
	direction_vector[0][0][2] = Obj1.direction[2], direction_vector[1][0][2] = Obj1.direction[2] * Obj1.length.z;

	//Obj2
	direction_vector[0][1][0] = Obj2.direction[0], direction_vector[1][1][0] = Obj2.direction[0] * Obj2.length.x;
	direction_vector[0][1][1] = Obj2.direction[1], direction_vector[1][1][1] = Obj2.direction[1] * Obj2.length.y;
	direction_vector[0][1][2] = Obj2.direction[2], direction_vector[1][1][2] = Obj2.direction[2] * Obj2.length.z;

	//平面の分離軸
	//AorB
	for (int i = 0; i < 2; ++i)
	{
		//xyz
		for (int k = 0; k < 3; ++k)
		{
			GLfloat ra = direction_vector[1][i][k].length();
			GLfloat rb = lenSegOnSparateAxis(&direction_vector[0][i][k], &direction_vector[1][i ? 0 : 1][0], &direction_vector[1][i ? 0 : 1][1], &direction_vector[1][i ? 0 : 1][2]);
			GLfloat length = glm::abs(glm::dot(interval, direction_vector[0][i][k]));
			if (length > ra + rb)
				return false;
		}
	}

	glm::vec3 cross;
	//垂直な分離軸
	//Aのxyz
	for (int i = 0; i < 3; ++i)
	{
		//Bのxyz
		for (int k = 0; k < 3; ++k)
		{
			cross = glm::cross(direction_vector[0][0][i], direction_vector[0][1][k]);

			glm::vec3 target[2][2];
				for (int l = 0,count = 0; l < 3; ++l)
				{
					if (l == i)
						continue;
					target[0][count++] = direction_vector[1][0][l];
				}
				for (int l = 0,count = 0; l < 3; ++l)
				{
					if (l == k)
						continue;
					target[1][count++] = direction_vector[1][1][l];
				}

				GLfloat ra = lenSegOnSparateAxis(&cross, &target[0][0], &target[0][1]);
				GLfloat rb = lenSegOnSparateAxis(&cross, &target[1][0], &target[1][1]);
				GLfloat length = glm::abs(glm::dot(interval, cross));

				if (length > ra + rb)
					return false;
		}
	}

	return true;
}

float Collision::lenSegOnSparateAxis(glm::vec3 * Sep, glm::vec3 * E1, glm::vec3 * E2, glm::vec3 * E3)
{
	GLfloat r1 = glm::abs(glm::dot(*Sep, *E1));
	GLfloat r2 = glm::abs(glm::dot(*Sep, *E2));
	GLfloat r3 = E3 ? glm::abs(glm::dot(*Sep, *E3)) : 0;
	return r1 + r2 + r3;
}