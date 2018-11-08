#pragma once

#include "GuardianManager.h"

#include "../../../../Entity/Entity.h"

class GuardianManager
{
public:
	GuardianManager() {}
	virtual ~GuardianManager() {}
public:
	virtual void Update(Entity::MATRIX3D& _matrix) = 0;
};