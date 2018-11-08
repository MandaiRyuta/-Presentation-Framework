#pragma once

#include "GuardianManager.h"

class Guardian01 : public GuardianManager
{
public:
	Guardian01() 
		: GuardianManager()
	{
		time_ = 1.5f;
	}
	~Guardian01() {}
public:
	void Update(Entity::MATRIX3D& _matrix) override;
private:
	float time_;
};