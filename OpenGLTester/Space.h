#pragma once
#include "Shape.h"
#include "AABB.h"

class Model;

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
	void bindModel(Model* Object);
	void addShape(Shape* Object);
	void removeShape(Shape* Object);
	void deleteModel(Model* Object);
	void serch(Shape* const Target, std::vector<Model*>& ExistListBuffer);

private:
	Model* target_;
	AABB range_;
	std::unordered_map<int, std::list<std::pair<const Shape*,Model*>>> space_;		//空間の番号とその空間に属しているオブジェクトのリスト
	std::unordered_map<const Shape*, int> shape_list_;
};