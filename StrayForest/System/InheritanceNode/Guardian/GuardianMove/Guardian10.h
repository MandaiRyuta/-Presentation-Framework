#pragma once
#include "GuardianManager.h"

class Guardian10 : public GuardianManager
{
public:
	Guardian10()
		: GuardianManager()
	{
		time_ = 7.5f;
	}
	~Guardian10() {}
public:
	void Update(Entity::MATRIX3D& _matrix) override;
private:
	float time_;
};
