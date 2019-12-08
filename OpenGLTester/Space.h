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
	void regist(Model* Object);
	void unregist(Model* Object);
	void serch(Shape* const Target, std::vector<Model*>& ExistListBuffer);

private:
	AABB range_;
	std::unordered_map<int, std::list<std::pair<const Shape*,Model*>>> space_;		//��Ԃ̔ԍ��Ƃ��̋�Ԃɑ����Ă���I�u�W�F�N�g�̃��X�g
	std::unordered_map<const Shape*, int> shape_list_;
};