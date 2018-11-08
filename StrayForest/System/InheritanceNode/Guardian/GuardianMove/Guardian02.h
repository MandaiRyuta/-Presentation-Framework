#pragma once

#include "GuardianManager.h"

class Guardian02 : public GuardianManager
{
public:
	Guardian02() 
		: GuardianManager()
	{
		time_ = 3.0f;
	}
	~Guardian02() {}
public:
	void Update(Entity::MATRIX3D& _matrix) override;
private:
	float time_;
};