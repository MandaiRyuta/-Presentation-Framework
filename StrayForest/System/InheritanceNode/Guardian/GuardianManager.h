#pragma once

#include "GuardianManager.h"

#include "../../../Entity/Entity.h"
#include <list>

class Guardian;

class GuardianManager
{
public:
	GuardianManager() {}
	virtual ~GuardianManager() {}
public:
	Guardian* Create();
public:
	void Update();
	void Draw();
private:
	std::list<Guardian*> guardians_;
};