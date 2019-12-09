#include "stdafx.h"
#include "Collision.h"

template <typename T>
T* changeClass(Shape* shape) { return dynamic_cast<T*>(shape); }

const float kConsiderZero = 0.000001F;


Collision::Collision()
{
}


Collision::~Collision()
{
}

//分離境界軸判定
bool Collision::OBBtoOBB(const OBB & Obj1, const OBB & Obj2)
{
	//OBBの中心間のベクトル
	glm::vec3 interval = Obj1.getCenter() - Obj2.getCenter();

	//各方向ベクトル
	//[nomal,denomal][a,b][x,y,z]
	glm::vec3 direction_vector[2][2][3];
	//Obj1
	direction_vector[0][0][0] = Obj1.getDirection(0), direction_vector[1][0][0] = Obj1.getDirection(0) * Obj1.getLength().x;
	direction_vector[0][0][1] = Obj1.getDirection(1), direction_vector[1][0][1] = Obj1.getDirection(1) * Obj1.getLength().y;
	direction_vector[0][0][2] = Obj1.getDirection(2), direction_vector[1][0][2] = Obj1.getDirection(2) * Obj1.getLength().z;

	//Obj2
	direction_vector[0][1][0] = Obj2.getDirection(0), direction_vector[1][1][0] = Obj2.getDirection(0) * Obj2.getLength().x;
	direction_vector[0][1][1] = Obj2.getDirection(1), direction_vector[1][1][1] = Obj2.getDirection(1) * Obj2.getLength().y;
	direction_vector[0][1][2] = Obj2.getDirection(2), direction_vector[1][1][2] = Obj2.getDirection(2) * Obj2.getLength().z;

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

	//垂直な分離軸
	//Aのxyz
	for (int i = 0; i < 3; ++i)
	{
		//Bのxyz
		for (int k = 0; k < 3; ++k)
		{
			glm::vec3 cross = glm::cross(direction_vector[0][0][i], direction_vector[0][1][k]);

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

//球同士の判定
bool Collision::SpheretoSphere(const Sphere & Obj1, const Sphere & Obj2)
{
	//重心の距離を求める
	float length = glm::length(Obj1.getCenterPoint() - Obj2.getCenterPoint());
	//半径との長さを比較
	if (length <= Obj1.getRadius() + Obj2.getRadius())
		return true;
	return false;
}

//BOX同士の判定
bool Collision::AABBtoAABB(const AABB & Obj1, const AABB & Obj2)
{
	//2Dの箱と箱の判定を次元数分行う
	//基準がObj1
	if (Obj1.getMin().x > Obj2.getMax().x)
		return false;
	if (Obj1.getMin().y > Obj2.getMax().y)
		return false;
	if (Obj1.getMin().z > Obj2.getMax().z)
		return false;

	//基準がObj2
	if (Obj2.getMin().x > Obj1.getMax().x)
		return false;
	if (Obj2.getMin().y > Obj1.getMax().y)
		return false;
	if (Obj2.getMin().z > Obj1.getMax().z)
		return false;

	return true;
}

////カプセル同士の判定( 衝突判定点破棄 )
//bool Collision::CapsuletoCapsule(const Capsule & Obj1, const Capsule & Obj2)
//{
//	glm::vec3 p[2];
//	float t[2];
//	float length = lengthSegmenttoSegment(Obj1.line, Obj2.line, p[0], p[1], t[0], t[1]);
//	if (Obj1.radius + Obj2.radius >= length)
//		return true;
//	return false;
//}
//
////カプセル同士の判定( 衝突判定点保持 )
//bool Collision::CapsuletoCapsule(const Capsule & Obj1, const Capsule & Obj2, glm::vec3 & Perpendicular1, glm::vec3 & Perpendicular2, float& Coefficient1, float& Coefficient2)
//{
//	float length = lengthSegmenttoSegment(Obj1.line, Obj2.line, Perpendicular1, Perpendicular2, Coefficient1, Coefficient2);
//	if (Obj1.radius + Obj2.radius <= length)
//		return true;
//	return false;
//}

//レイと平面
bool Collision::RaytoPlane(const Segment & Segment, const glm::vec3& Point, const glm::vec3& Nomal)
{
	if (glm::dot(Segment.getStart() - Point, Nomal) * glm::dot(Segment.getEnd() - Point,Nomal) <= 0.0F)
		return true;
	return false;
}

//点とポリゴン
bool Collision::PointtoPoligon(glm::vec3 Point, const Poligon& Poligon)
{
	glm::vec3 vector[3] =
	{ Poligon.getPoint(1) - Poligon.getPoint(0),
	Poligon.getPoint(2) - Poligon.getPoint(1),
	Poligon.getPoint(0) - Poligon.getPoint(2) };

	for (int i = 0; i < 3; ++i)
	{
		glm::vec3 check = glm::normalize(glm::cross(vector[0], Point - Poligon.getPoint(0)));
		if (glm::abs(check.x - Poligon.getNomal().x) > kConsiderZero&&
			glm::abs(check.y - Poligon.getNomal().y) > kConsiderZero&&
			glm::abs(check.z - Poligon.getNomal().z) > kConsiderZero)
			return false;
	}

	return true;
}

//線と平面の衝突判定位置
glm::vec3 Collision::intersectionLinetoPlane(const Segment& Segment, const glm::vec3& Point, const glm::vec3& Nomal)
{
	float d1, d2;
	//平面までの距離
	d1 = lengthPointtoPlane(Segment.getStart(), Point,Nomal);
	d2 = lengthPointtoPlane(Segment.getEnd(), Point,Nomal);
	//交点までの係数
	float a = d1 / (d1 + d2);
	//交点
	glm::vec3 intersection = Segment.getStart() + a * Segment.getRay();
	return intersection;
}

//OBBと平面の判定
bool Collision::OBBtoPlane(const OBB & Obj1, const glm::vec3& Point, const glm::vec3& Nomal,float* RepelAmount)
{
	//平面の法線に対するOBBの射影線の長さ
	float obb_radius = 0.0F;
	//X軸成分
	obb_radius += glm::abs(glm::dot(Nomal, Obj1.getDirection(0) * Obj1.getLength().x));
	//Y成分
	obb_radius += glm::abs(glm::dot(Nomal, Obj1.getDirection(1) * Obj1.getLength().y));
	//Z成分
	obb_radius += glm::abs(glm::dot(Nomal, Obj1.getDirection(2) * Obj1.getLength().z));

	//平面とOBBの距離
	float length = glm::dot(Nomal, Point - Obj1.getCenter());

	//戻し量を返却
	if (RepelAmount != nullptr)
		if (length > 0.0F)
			*RepelAmount = obb_radius - glm::abs(length);
		else
			*RepelAmount = obb_radius + glm::abs(length);

	if (glm::abs(length) - obb_radius < 0.0F)
		return true;

	return false;
}

//OBBとAABBの判定
bool Collision::OBBtoAABB(const OBB & Obj1, const AABB & Obj2)
{
	//AABBをOBBに変換
	OBB obb;
	obb.setCenter((Obj2.getMax() - Obj2.getMin()) * 0.5F);
	obb.setLength(Obj2.getMax() - obb.getCenter());
	for (int i = 0; i < 3; ++i)
		obb.setDirection(i, glm::mat4(1.0F)[i]);
	return OBBtoOBB(Obj1,obb);
}

//レイと平面
bool Collision::LinetoPlane(const Segment & Segment, const glm::vec3& Point, const glm::vec3& Nomal)
{
	//線分が平面上に存在する
	if (glm::dot(Segment.getStart() - Point, Nomal) < kConsiderZero)
		return true;
	//平面の法線と線分が垂直に交わらない( 平面と平行ではない )
	if (glm::dot(Segment.getRay(), Nomal) > kConsiderZero)
		return true;
	return false;
}

//直線と直線の最短距離
float Collision::lengthLinetoLine(const Segment & Line1, const Segment & Line2, glm::vec3 & PBuffer1, glm::vec3 & PBuffer2, float & CBuffer1, float & CBuffer2)
{
	//平行判定
	if (glm::length(glm::cross(Line1.getRay(), Line2.getRay())) < kConsiderZero)
	{
		float length = lengthPointtoLine(Line1.getStart(), Line2, PBuffer2, CBuffer2);
		PBuffer1 = Line1.getStart();
		CBuffer1 = 0.0F;
		return length;
	}

	//ねじれの位置関係
	float dot_line12 = glm::dot(Line1.getRay(), Line2.getRay());
	float lengthsq_line1 = glm::dot(Line1.getRay(), Line2.getRay());
	float lengthsq_line2 = glm::dot(Line2.getRay(), Line2.getRay());
	glm::vec3 vec_line12 = Line1.getStart() - Line2.getStart();
	CBuffer1 = (dot_line12 * glm::dot(Line2.getRay(), vec_line12) - lengthsq_line2 * glm::dot(Line1.getRay(), vec_line12)) /
		(lengthsq_line1 * lengthsq_line2 - dot_line12 * dot_line12);
	PBuffer1 = Line1.getStart() + CBuffer1 * (Line1.getRay());
	CBuffer2 = glm::dot(Line2.getRay(), PBuffer1 - Line2.getStart()) / lengthsq_line2;
	PBuffer2 = Line2.getStart() + CBuffer2 * Line2.getRay();

	return glm::length(PBuffer2 - PBuffer1);
}

//点から平面の距離
float Collision::lengthPointtoPlane(const glm::vec3 Point, const glm::vec3& PlanePoint, const glm::vec3& Nomal)
{
	float length = std::abs(glm::dot(Nomal, Point - PlanePoint)) / glm::length(Nomal);
	return length;
}

//点からOBBの最短距離
float Collision::lengthPointoOBB(const glm::vec3 & Point, const OBB & Obj)
{
	return 0.0f;
}

//点からAABBの最短距離
float Collision::lengthPointoAABB(const glm::vec3 & Point, const AABB & Obj)
{
	return 0.0f;
}

//分離境界軸の作成
float Collision::lenSegOnSparateAxis(glm::vec3 * Sep, glm::vec3 * E1, glm::vec3 * E2, glm::vec3 * E3)
{
	//分離境界線軸の長さを計算
	GLfloat r1 = glm::abs(glm::dot(*Sep, *E1));
	GLfloat r2 = glm::abs(glm::dot(*Sep, *E2));
	GLfloat r3 = E3 != nullptr ? glm::abs(glm::dot(*Sep, *E3)) : 0;
	return r1 + r2 + r3;
}

//レイとレイの最短距離
float Collision::lengthSegmenttoSegment(const Segment & Segment1, const Segment & Segment2, glm::vec3 & PBuffer1, glm::vec3 & PBuffer2, float & CBuffer1, float & CBuffer2)
{
	float length = 0.0F;

	//線分の始点と終点がほぼほぼ一致している場合
	if (glm::dot(Segment1.getRay(), Segment1.getRay()) < kConsiderZero)
	{
		if (glm::dot(Segment2.getRay(), Segment2.getRay()) < kConsiderZero)
		{
			length = glm::length(Segment2.getStart() - Segment1.getStart());
			PBuffer1 = Segment1.getStart();
			PBuffer2 = Segment2.getStart();
			CBuffer1 = CBuffer2 = 0.0F;
			return length;
		}
		else
		{
			length = lengthPointtoLine(Segment1.getStart(), Segment2, PBuffer2, CBuffer2);
			PBuffer1 = Segment1.getStart();
			CBuffer1 = 0.0F;
			return length;
		}
	}
	else if (glm::dot(Segment2.getRay(), Segment2.getRay()) < kConsiderZero)
	{
		length = lengthPointtoLine(Segment2.getStart(), Segment1, PBuffer1, CBuffer1);
		PBuffer2 = Segment2.getStart();
		CBuffer2 = 0.0F;
		return length;
	}

	//平行判定
	if (glm::length(glm::cross(Segment1.getRay(), Segment2.getRay())) <= kConsiderZero)
	{
		length = glm::min(lengthPointtoLine(Segment1.getStart(), Segment2, PBuffer2, CBuffer2), lengthPointtoLine(Segment2.getStart(), Segment1, PBuffer1, CBuffer1));
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
	PBuffer1 = Segment1.getStart() + CBuffer1 * (Segment1.getRay());
	length = lengthPointtoLine(PBuffer1, Segment2, PBuffer2, CBuffer2);
	if (CBuffer2 >= 0.0F && CBuffer2 <= 1.0F)
		return length;

	//Swgment2側が外側だったのでSegment2をクランプ
	CBuffer2 = glm::clamp(CBuffer2, 0.0F, 1.0F);
	PBuffer2 = Segment2.getStart() + CBuffer2 * (Segment2.getRay());
	length = lengthPointtoLine(PBuffer2, Segment1, PBuffer1, CBuffer1);
	if (CBuffer1 >= 0.0F && CBuffer1 <= 1.0F)
		return length;

	//双方の端点が最短距離
	CBuffer1 = glm::clamp(CBuffer1, 0.0F, 1.0F);
	PBuffer1 = Segment1.getStart() + CBuffer1 * (Segment1.getRay());
	return glm::length(PBuffer2 - PBuffer1);
}

//点と直線の距離
float Collision::lengthPointtoLine(const glm::vec3 Point, const Segment & Segment, glm::vec3 & PBuffer, float & CBuffer)
{
	CBuffer = 0.0F;
	glm::vec3 line = Segment.getRay();
	if (glm::dot(line, line) > 0.0F)
		CBuffer = glm::dot(line, Point - Segment.getStart()) / glm::dot(line, line);

	PBuffer = Segment.getStart() + CBuffer * line;
	float length = glm::length(PBuffer - Point);

	if (!sharpAngle(Point, Segment.getStart(), Segment.getEnd()))
		length = glm::length(Segment.getStart() - Point);
	else if (!sharpAngle(Point, Segment.getEnd(), Segment.getStart()))
		length = glm::length(Segment.getEnd() - Point);
	return length;
}

//鋭角判定
bool Collision::sharpAngle(const glm::vec3 & Point1, glm::vec3 Point2, glm::vec3 Point3)
{
	glm::vec3 line[2] = { Point1 - Point2,
		Point3 - Point2 };

	if (glm::dot(line[0], line[1]) > 0.0F)
		return true;
	return false;
}
