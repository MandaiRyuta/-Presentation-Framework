#pragma once

#include "GuardianManager.h"

class Guardian07 : public GuardianManager
{
public:
	Guardian07() 
		: GuardianManager()
	{
		time_ = 4.5f;
	}
	~Guardian07() {}
public:
	void Update(Entity::MATRIX3D& _matrix) override;
private:
	float time_;
};