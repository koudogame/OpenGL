#include "stdafx.h"
#include "Space.h"
#include "Collision.h"
#include "Model.h"
#include "Shape.h"

const int kDimention = 3;
const int kDivideLevel = 3;		//空間分割レベル
const int kDivideNum = 8;		//分割数

const AABB kRange = AABB(glm::vec3(60.0F), glm::vec3(-60.0F));

int toMoton(const AABB& Range, const glm::vec3 Point);
int toMoton(const AABB& Range, const glm::vec3 Max, glm::vec3 Min);
int bitStepTo3D(GLbyte Num);

Space::Space()
{
	range_ = kRange;
}

Space::~Space()
{
}

void Space::Redefinition(AABB Range)
{
	range_ = Range;
}

//空間へ登録
void Space::regist(Model * Object)
{
	unregist(Object);
	for (auto& itr : Object->getShape())
	{
		auto shape = dynamic_cast<const Complex*>(&itr);
		AABB box = (shape == nullptr ? *dynamic_cast<const AABB*>(&itr) : shape->box);
		int kBlock = toMoton(range_, box.max, box.min);

		if (kBlock == -1)
			return;
		shape_list_[&itr] = kBlock;
		space_[kBlock].push_back(std::make_pair(&itr, Object));
	}
}

//空間への登録解除
void Space::unregist(Model * Object)
{
	for (auto& shape : Object->getShape())
	{
		int moton = shape_list_[&shape];
		for (auto itr = space_[moton].begin(), end = space_[moton].end();
			itr != end;++itr)
		{
			if ((*itr) == std::pair<const Shape*, Model*>(&shape, Object))
			{
				itr = space_[moton].erase(itr);
				if (space_[moton].size() == 0)
					space_.erase(moton);
				break;
			}
		}
		shape_list_.erase(&shape);
	}
}

//当たり判定ありのオブジェクトの検索
void Space::serch(Shape * const Target, std::vector<Model*>& ExistListBuffer)
{
	//ルート空間までの親と判定
	for (int pearent = shape_list_[Target];; pearent >>= 3)
	{
		for (auto& pearent_shape : space_[pearent])
			if (Collision::get()->collision(Target, pearent_shape.first))
				ExistListBuffer.push_back(pearent_shape.second);

		if (pearent == 0)
			break;
	}
}

//指定頂点のモートン番号を算出
int toMoton(const AABB& Range, const glm::vec3 Point)
{
	const int kLineNUm = static_cast<int>(std::pow(2, kDivideLevel));

	glm::vec3 range = Range.max - Range.min;

	//範囲内でのモートン番号を求める
	const int kMotonX = static_cast<int>(Point.x / range.x);
	const int kMotonY = static_cast<int>(Point.y / range.y);
	const int kMotonZ = static_cast<int>(Point.z / range.z);
	return bitStepTo3D(kMotonX) | (bitStepTo3D(kMotonY) << 1) | (bitStepTo3D(kMotonZ) << 2);
}

//BOXの所属する空間のモートン番号を算出
int toMoton(const AABB& Range, const glm::vec3 Max, glm::vec3 Min)
{
	//範囲外オブジェクト
	if (!Collision::get()->AABBtoAABB(Range, AABB(Max, Min)))
		return -1;

	const int kXorMoton = toMoton(Range, Max) ^ toMoton(Range, Min);

	//所属空間レベルを調べる
	int level = kDivideLevel;
	if (kXorMoton != 0)
	{
		level = 0;

		for (int i = kDivideLevel - 1; i >= 0; --i)
		{
			//所属空間が判明
			if (kXorMoton & (0x7) << (i * 3))
				break;
			//空間レベルを子へ
			else
				++level;
		}
	}

	//空間へ登録
	int block = (static_cast<int>(std::pow(kDivideNum, level)) - 1) / (kDivideNum - 1);
	return block += toMoton(Range, Max) >> ((kDivideLevel - level) * 3);
}

int bitStepTo3D(GLbyte Num)
{
	Num = (Num | (Num << 8)) & 0x0000F00F;
	Num = (Num | (Num << 4)) & 0x000C30C3;
	Num = (Num | (Num << 2)) & 0x00249249;
	return Num;
}
