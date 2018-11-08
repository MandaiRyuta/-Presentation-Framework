#pragma once
#include "GuardianManager.h"

class Guardian09 : public GuardianManager
{
public:
	Guardian09()
		: GuardianManager()
	{
		time_ = 7.5f;
	}
	~Guardian09() {}
public:
	void Update(Entity::MATRIX3D& _matrix) override;
private:
	float time_;
};