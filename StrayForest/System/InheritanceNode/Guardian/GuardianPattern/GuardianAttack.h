#pragma once
#include "GuardiansPattern.h"

class GuardianAttack : public GuardianPattern
{
public:
	GuardianAttack();
	virtual ~GuardianAttack();
	virtual void Update(Guardian* _guardian) override;
};