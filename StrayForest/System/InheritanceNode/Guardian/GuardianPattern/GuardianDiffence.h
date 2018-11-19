#pragma once
#include "GuardiansPattern.h"

class GuardianDiffence : public GuardianPattern
{
public:
	GuardianDiffence();
	virtual ~GuardianDiffence();
	virtual void Update(Guardian* _guardian) override;
};