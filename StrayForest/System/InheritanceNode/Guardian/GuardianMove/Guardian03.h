#pragma once

#include "GuardianManager.h"

class Guardian03 : public GuardianManager
{
public:
	Guardian03() 
		: GuardianManager() 
	{
		time_ = 4.5f;
	}
	~Guardian03() {}

public:
	void Update(Entity::MATRIX3D& _matrix) override;
private:
	float time_;
};