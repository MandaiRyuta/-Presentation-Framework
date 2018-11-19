#pragma once

class Guardian;

class GuardianPattern
{
public:
	GuardianPattern() {}
	virtual ~GuardianPattern() {}
	virtual void Update(Guardian* _guardian) = 0;
};

class GuardianPatternNull : public GuardianPattern
{
public:
	GuardianPatternNull() {}
	~GuardianPatternNull(){}
	virtual void Update(Guardian* _guardian) override {}
};