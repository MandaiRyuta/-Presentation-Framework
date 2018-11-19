#pragma once
#include "GuardiansPattern.h"

class GuardianNomal : public GuardianPattern
{
public:
	GuardianNomal();
	virtual ~GuardianNomal();
	virtual void Update(Guardian* _guardian) override;
};