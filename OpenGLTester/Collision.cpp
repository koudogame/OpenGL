#include "stdafx.h"
#include "Collision.h"

const float kConsiderZero = 0.000001F;


Collision::Collision()
{
}


Collision::~Collision()
{
}

bool Collision::OBBtoOBB(const OBB & Obj1, const OBB & Obj2)
{
	//OBBの中心間のベクトル
	glm::vec3 interval = Obj1.c_gravity - Obj2.c_gravity;

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
			GLfloat ra = glm::abs(glm::dot(direction_vector[1][i][k], direction_vector[0][i][k]));
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
			for (int l = 0, count = 0; l < 3; ++l)
			{
				if (l == i)
					continue;
				target[0][count++] = direction_vector[1][0][l];
			}
			for (int l = 0, count = 0; l < 3; ++l)
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

bool Collision::SpheretoSphere(const Sphere & Obj1, const Sphere & Obj2)
{
	//重心の距離を求める
	float length = glm::length(Obj1.c_gravity - Obj2.c_gravity);
	//半径との長さを比較
	if (length <= Obj1.radius + Obj2.radius)
		return true;
	return false;
}

bool Collision::AABBtoAABB(const AABB & Obj1, const AABB & Obj2)
{
	//2Dの箱と箱の判定を次元数分行う
	//基準がObj1
	if (Obj1.min.x > Obj2.max.x)
		return false;
	if (Obj1.min.y > Obj2.max.y)
		return false;
	if (Obj1.min.z > Obj2.max.z)
		return false;

	//基準がObj2
	if (Obj2.min.x > Obj1.max.x)
		return false;
	if (Obj2.min.y > Obj1.max.y)
		return false;
	if (Obj2.min.z > Obj1.max.z)
		return false;

	return true;
}

bool Collision::CapsuletoCapsule(const Capsule & Obj1, const Capsule & Obj2)
{
	glm::vec3 p[2];
	float t[2];
	float length = lengthSegmenttoSegment(Obj1.line, Obj2.line, p[0], p[1], t[0], t[1]);
	if (Obj1.radius + Obj2.radius >= length)
		return true;
	return false;
}

bool Collision::CapsuletoCapsule(const Capsule & Obj1, const Capsule & Obj2, glm::vec3 & Perpendicular1, glm::vec3 & Perpendicular2, float& Coefficient1, float& Coefficient2)
{
	float length = lengthSegmenttoSegment(Obj1.line, Obj2.line, Perpendicular1, Perpendicular2, Coefficient1, Coefficient2);
	if (Obj1.radius + Obj2.radius <= length)
		return true;
	return false;
}

bool Collision::RaytoPlane(const Line & Segment, const glm::vec3 & Nomal, const glm::vec3 & NomalPoint)
{
	if (glm::dot(Segment.start - NomalPoint, Nomal) * glm::dot(Segment.end - NomalPoint, Nomal) <= 0.0F)
		return true;
	return false;
}

bool Collision::LinetoPlane(const Line & Segment, glm::vec3 PlanePoint, glm::vec3 Nomal)
{
	//線分が平面上に存在する
	if (glm::dot(Segment.start - PlanePoint, Nomal) < kConsiderZero)
		return true;
	//平面の法線と線分が垂直に交わらない( 平面と平行ではない )
	if (glm::dot(Segment.end - Segment.start, Nomal) > kConsiderZero)
		return true;
	return false;
}

float Collision::lengthLinetoLine(const Line & Line1, const Line & Line2, glm::vec3 & PBuffer1, glm::vec3 & PBuffer2, float & CBuffer1, float & CBuffer2)
{
	//平行判定
	if (glm::length(glm::cross(Line1.end - Line1.start, Line2.end - Line2.start)) < kConsiderZero)
	{
		float length = lengthPointtoLine(Line1.start, Line2, PBuffer2, CBuffer2);
		PBuffer1 = Line1.start;
		CBuffer1 = 0.0F;
		return length;
	}

	//ねじれの位置関係
	float dot_line12 = glm::dot(Line1.end - Line1.start, Line2.end - Line2.start);
	float lengthsq_line1 = glm::dot(Line1.end - Line1.start, Line1.end - Line1.start);;
	float lengthsq_line2 = glm::dot(Line2.end - Line2.start, Line2.end - Line2.start);;
	glm::vec3 vec_line12 = Line1.start - Line2.start;
	CBuffer1 = (dot_line12 * glm::dot(Line2.end - Line2.start, vec_line12) - lengthsq_line2 * glm::dot(Line1.end - Line1.start, vec_line12)) /
		(lengthsq_line1 * lengthsq_line2 - dot_line12 * dot_line12);
	PBuffer1 = Line1.start + CBuffer1 * (Line1.end - Line1.start);
	CBuffer2 = glm::dot(Line2.end - Line2.start, PBuffer1 - Line2.start) / lengthsq_line2;
	PBuffer2 = Line2.start + CBuffer2 * (Line2.end - Line2.start);

	return glm::length(PBuffer2 - PBuffer1);
}

float Collision::lengthPointtoPlane(const glm::vec3 Point, glm::vec3 Nomal,glm::vec3 NomalPoint)
{
	float length = std::abs(glm::dot(Nomal, Point - NomalPoint)) / glm::length(Nomal);
	return length;
}

float Collision::lenSegOnSparateAxis(glm::vec3 * Sep, glm::vec3 * E1, glm::vec3 * E2, glm::vec3 * E3)
{
	//分離境界線軸の長さを計算
	GLfloat r1 = glm::abs(glm::dot(*Sep, *E1));
	GLfloat r2 = glm::abs(glm::dot(*Sep, *E2));
	GLfloat r3 = E3 ? glm::abs(glm::dot(*Sep, *E3)) : 0;
	return r1 + r2 + r3;
}

float Collision::lengthSegmenttoSegment(const Line & Segment1, const Line & Segment2, glm::vec3 & PBuffer1, glm::vec3 & PBuffer2, float & CBuffer1, float & CBuffer2)
{
	float length = 0.0F;

	//線分の始点と終点がほぼほぼ一致している場合
	if (glm::dot(Segment1.end - Segment1.start, Segment1.end - Segment1.start) < kConsiderZero)
	{
		if (glm::dot(Segment2.end - Segment2.start, Segment2.end - Segment2.start) < kConsiderZero)
		{
			length = glm::length(Segment2.start - Segment1.start);
			PBuffer1 = Segment1.start;
			PBuffer2 = Segment2.start;
			CBuffer1 = CBuffer2 = 0.0F;
			return length;
		}
		else
		{
			length = lengthPointtoLine(Segment1.start, Segment2, PBuffer2, CBuffer2);
			PBuffer1 = Segment1.start;
			CBuffer1 = 0.0F;
			return length;
		}
	}
	else if (glm::dot(Segment2.end - Segment2.start, Segment2.end - Segment2.start) < kConsiderZero)
	{
		length = lengthPointtoLine(Segment2.start, Segment1, PBuffer1, CBuffer1);
		PBuffer2 = Segment2.start;
		CBuffer2 = 0.0F;
		return length;
	}

	//平行判定
	if (glm::length(glm::cross(Segment1.end - Segment1.start, Segment2.end - Segment2.start)) == 0.0F)
	{
		length = glm::min(lengthPointtoLine(Segment1.start, Segment2, PBuffer2, CBuffer2), lengthPointtoLine(Segment2.start, Segment1, PBuffer1, CBuffer1));
		return length;
	}
	//ねじれの関係
	else
	{
		length = lengthLinetoLine(Segment1, Segment2, PBuffer1, PBuffer2, CBuffer1, CBuffer2);
		if (CBuffer1 >= 0.0F && CBuffer1 <= 1.0F &&
			CBuffer2 >= 0.0F && CBuffer2 <= 1.0F)
			return length;
	}

	//垂線の足が線分の外側に存在
	//Segment1側のCBufferを0~1にクランプして垂線を降ろす
	CBuffer1 = glm::clamp(CBuffer1, 0.0F, 1.0F);
	PBuffer1 = Segment1.start + CBuffer1 * (Segment1.end - Segment1.start);
	length = lengthPointtoLine(PBuffer1, Segment2, PBuffer2, CBuffer2);
	if (CBuffer2 >= 0.0F && CBuffer2 <= 1.0F)
		return length;

	//Swgment2側が外側だったのでSegment2をクランプ
	CBuffer2 = glm::clamp(CBuffer2, 0.0F, 1.0F);
	PBuffer2 = Segment2.start + CBuffer2 * (Segment2.end - Segment2.start);
	length = lengthPointtoLine(PBuffer2, Segment1, PBuffer1, CBuffer1);
	if (CBuffer1 >= 0.0F && CBuffer1 <= 1.0F)
		return length;

	//双方の端点が最短距離
	CBuffer1 = glm::clamp(CBuffer1, 0.0F, 1.0F);
	PBuffer1 = Segment1.start + CBuffer1 * (Segment1.end - Segment1.start);
	return glm::length(PBuffer2 - PBuffer1);
}

float Collision::lengthPointtoLine(const glm::vec3 Point, const Line & Line, glm::vec3 & PBuffer, float & CBuffer)
{
	CBuffer = 0.0F;
	glm::vec3 line = Line.end - Line.start;
	if (glm::dot(line,line) > 0.0F)
		CBuffer = glm::dot(line,  Point - Line.start) / glm::dot(line, line);

	PBuffer = Line.start + CBuffer * line;
	float length = glm::length(PBuffer - Point);

	if (!sharpAngle(Point, Line.start, Line.end))
		length = glm::length(Line.start - Point);
	else if (!sharpAngle(Point, Line.end, Line.start))
		length = glm::length(Line.end - Point);
	return length;
}

bool Collision::sharpAngle(const glm::vec3 & Point1, glm::vec3 Point2, glm::vec3 Point3)
{
	glm::vec3 line[2] = { Point1 - Point2,
		Point3 - Point2 };

	if (glm::dot(line[0], line[1]) > 0.0F)
		return true;
	return false;
}
