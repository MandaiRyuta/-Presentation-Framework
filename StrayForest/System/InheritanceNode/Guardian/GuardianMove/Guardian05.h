#pragma once
#include "GuardianManager.h"

class Guardian05 : public GuardianManager
{
public:
	Guardian05() 
		: GuardianManager()
	{
		time_ = 1.5f;
	}
	~Guardian05() {}
public:
	void Update(Entity::MATRIX3D& _matrix) override;
private:
	float time_;
};