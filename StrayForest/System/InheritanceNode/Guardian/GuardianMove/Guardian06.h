#pragma once

#include "GuardianManager.h"

class Guardian06 : public GuardianManager
{
public:
	Guardian06() 
		: GuardianManager()
	{
		time_ = 3.0f;
	}
	~Guardian06() {}
public:
	void Update(Entity::MATRIX3D& _matrix) override;
private:
	float time_;
};