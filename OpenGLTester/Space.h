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
	void regist(Shape* Object);
	void unregist(Shape* Object);
	void collision();
	void serch(Shape* Target, std::vector<Object*>& ExistListBuffer);

private:
	AABB range_;
	std::unordered_map<int, std::list<Shape*>> space_;		//空間の番号とその空間に属しているオブジェクトのリスト
	std::unordered_map<Shape*, int> object_list_;	//オブジェクトとそのオブジェクトが属している空間番号
};