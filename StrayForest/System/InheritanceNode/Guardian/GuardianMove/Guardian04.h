#pragma once

#include "GuardianManager.h"

class Guardian04 : public GuardianManager
{
public:
	Guardian04() 
		: GuardianManager()
	{
		time_ = 6.0f;
	}
	~Guardian04() {}
public:
	void Update(Entity::MATRIX3D& _matrix) override;
private:
	float time_;
};