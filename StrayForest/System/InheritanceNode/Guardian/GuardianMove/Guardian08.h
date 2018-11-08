#pragma once

#include "GuardianManager.h"

class Guardian08 : public GuardianManager
{
public:
	Guardian08() 
		: GuardianManager() 
	{
		time_ = 6.0f;
	}
	~Guardian08() {}
public:
	void Update(Entity::MATRIX3D& _matrix) override;
private:
	float time_;
};