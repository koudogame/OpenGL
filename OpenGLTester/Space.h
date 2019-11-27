#pragma once
#include "Shape.h"
class Space
{
	//singleton
private:
	Space();
	Space(const Space&) = delete;
	Space operator=(const Space&) = delete;
public:
	inline static Space* get() { static Space instance; return &instance; }

public:
	~Space();

public:
	void Redefinition(AABB Range);
	void regist(AABB* Object);
	void unregist(AABB* Object);
	void collision();

private:
	AABB range_;
	std::unordered_map<int, std::list<AABB*>> space_;		//空間の番号とその空間に属しているオブジェクトのリスト
	std::unordered_map<AABB*, int> object_list_;	//オブジェクトとそのオブジェクトが属している空間番号
};