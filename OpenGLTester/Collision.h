#pragma once
#include "Model.h"
class Collision
{
private:
	Collision();
	Collision(const Collision&) = delete;
	Collision operator=(const Collision&) = delete;
public:
	static Collision* get() { static Collision instance; return &instance; }
	~Collision();

public:
	bool OBBtoOBB(const OBB& obj1, const OBB& obj2);

	float lenSegOnSparateAxis(glm::vec3 *n_ae1, glm::vec3 *be1, glm::vec3 *be2, glm::vec3 *be3 = 0);

};

